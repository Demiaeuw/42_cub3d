/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_path_gestion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:42:40 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/05 16:43:53 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	check_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strcmp(path + len - 4, ".xpm") != 0)
		return (0);
	return (1);
}

void	set_texture_path(char **destination, char *path)
{
	if (*destination != NULL)
	{
		free(*destination);
	}
	*destination = ft_strdup(path);
	if (*destination == NULL)
	{
		message_error("Failed to allocate memory for texture path");
	}
}

void	remove_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

void	path_gestion(char *filename, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		message_error("Failed to open file");
	line = get_next_line(fd);
	while (line)
	{
		remove_newline(line);
		if (ft_strncmp(line, "NO ", 3) == 0 && check_extension(line + 3))
			set_texture_path(&game->infos->path_north, line + 3);
		else if (ft_strncmp(line, "SO ", 3) == 0 && check_extension(line + 3))
			set_texture_path(&game->infos->path_south, line + 3);
		else if (ft_strncmp(line, "EA ", 3) == 0 && check_extension(line + 3))
			set_texture_path(&game->infos->path_east, line + 3);
		else if (ft_strncmp(line, "WE ", 3) == 0 && check_extension(line + 3))
			set_texture_path(&game->infos->path_west, line + 3);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!game->infos->path_north || !game->infos->path_south
		|| !game->infos->path_east || !game->infos->path_west)
		message_error("Missing one or more texture paths");
}
