/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_path_gestion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:42:33 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/30 12:24:24 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	path_gestion(char *filename, t_game **game)
{
	//ajouts des path a la structure											ok
	add_path(filename, game);
	//verification si c'est bien des .xpm										ok
	check_pathextension(*game);
}


void	add_path(char *filename, t_game **game)
{
	int		file;
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	int		i;

	i = 0;
	file = open(filename, O_RDONLY);

	while ((bytes_read = read(file, &buffer[i], 1)) > 0)
	{
		if (buffer[i] == '\n' || i >= BUFFER_SIZE -1)
		{
			buffer[i] = '\0';
			if (ft_strncmp(buffer, "NO ", 3) == 0)
				(*game)->infos->path_north = ft_strdup(buffer + 3);
			else if (ft_strncmp(buffer, "SO ", 3) == 0)
				(*game)->infos->path_south = ft_strdup(buffer + 3);
			else if (ft_strncmp(buffer, "EA ", 3) == 0)
				(*game)->infos->path_east = ft_strdup(buffer + 3);
			else if (ft_strncmp(buffer, "WE ", 3) == 0)
				(*game)->infos->path_west = ft_strdup(buffer + 3);
			i = 0;
		}
		else
			i++;
	}
	close(file);
}

int	has_xpm(const char *path) 
{
	const char *dot = ft_strrchr(path, '.');
	return (dot != NULL && ft_strcmp(dot, ".xpm") == 0);
}

void	check_pathextension(t_game *game)
{
	if (!has_xpm(game->infos->path_north)
		|| !has_xpm(game->infos->path_south)
		|| !has_xpm(game->infos->path_east)
		|| !has_xpm(game->infos->path_west))
		{
			//free struct
			message_error("One or more paths do not have the .xpm extension");
		}
}