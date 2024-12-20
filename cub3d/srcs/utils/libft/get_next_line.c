/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:46:02 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/05 16:31:07 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_a_next_line(int fd, char *str)
{
	char		*buf;
	int			isread;

	buf = malloc((BUFFER_SIZE_GNL + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	isread = 42;
	ft_memset(buf, 0, BUFFER_SIZE_GNL + 1);
	while (!ft_strrchr(buf, '\n') && isread != 0)
	{
		isread = read(fd, buf, BUFFER_SIZE_GNL);
		if (isread == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[isread] = '\0';
		if (str == NULL && isread != 0)
			str = ft_strdup(buf);
		else if (isread != 0)
			str = ft_strjoin_gnl(str, buf);
	}
	free(buf);
	return (str);
}

static char	*ft_the_real_line(char *str)
{
	char	*line;
	int		i;

	line = malloc(sizeof(char) * (ft_strlen_endl(str) + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_newstr(char *str)
{
	int		strlen;
	int		i;
	char	*newstr;

	strlen = ft_strlen_endl(str);
	if (!str[strlen] || (strlen == 0 && str[strlen] != '\n'))
	{
		free(str);
		return (NULL);
	}
	newstr = malloc(sizeof(char) * (ft_strlen(str) - strlen + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (str[strlen++])
		newstr[i++] = str[strlen];
	newstr[i] = '\0';
	free (str);
	if (newstr[0] == '\0')
	{
		free(newstr);
		return (NULL);
	}
	return (newstr);
}

char	*get_next_line(int fd)
{
	static char	*str[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE_GNL <= 0)
		return (NULL);
	str[fd] = ft_a_next_line(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = ft_the_real_line(str[fd]);
	str[fd] = ft_newstr(str[fd]);
	return (line);
}
