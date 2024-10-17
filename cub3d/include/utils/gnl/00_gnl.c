/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:15:53 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/17 15:22:50 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

char	*get_next_line(int fd)
{
	static char	*stash[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE_GNL <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = gnl_ad_to_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = gnl_line(stash[fd]);
	stash[fd] = gnl_clean_static(stash[fd]);
	return (line);
}

//lire et ajoute a la variable static en fonction de BUFFER_SIZE
char	*gnl_ad_to_stash(int fd, char *stash)
{
	char	*s;
	int		readed;

	readed = 1;
	s = gnl_calloc(BUFFER_SIZE_GNL + 1, sizeof(char));
	while (readed != 0)
	{
		readed = read(fd, s, BUFFER_SIZE_GNL);
		if (readed == -1)
		{
			free(s);
			return (NULL);
		}
		s[readed] = 0;
		stash = gnl_strjoin(stash, s);
		if (gnl_strchr(s, '\n'))
			break ;
	}
	free(s);
	return (stash);
}

//appel de la fonction qui lit et save de 0 a '\n'  dans une variable stash
char	*gnl_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = gnl_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] && stash[i] == '\n')
		line[i] = '\n';
	return (line);
}

//fonction qui clean la static et garde de '\n' a la fin 
char	*create_new_stash(char *stash, int i)
{
	int		j;
	char	*new_stash;

	new_stash = gnl_calloc((gnl_strlen(stash) - i + 1), sizeof(char));
	if (!new_stash)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
	{
		new_stash[j] = stash[i];
		i++;
		j++;
	}
	return (new_stash);
}

char	*gnl_clean_static(char *stash)
{
	int		i;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = create_new_stash(stash, i);
	free(stash);
	if (new_stash[0] == '\0')
	{
		free(new_stash);
		return (NULL);
	}
	return (new_stash);
}