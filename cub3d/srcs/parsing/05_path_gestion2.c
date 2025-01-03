/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_path_gestion2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:36:03 by kpourcel          #+#    #+#             */
/*   Updated: 2025/01/03 17:40:35 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		return (0);
	}
	close(fd);
	return (1);
}

void	check_texture_paths(t_game *game)
{
	if (game->infos->path_north && !file_exists(game->infos->path_north))
		message_error("North texture path is invalid", game);
	if (game->infos->path_south && !file_exists(game->infos->path_south))
		message_error("South texture path is invalid", game);
	if (game->infos->path_west && !file_exists(game->infos->path_west))
		message_error("West texture path is invalid", game);
	if (game->infos->path_east && !file_exists(game->infos->path_east))
		message_error("East texture path is invalid", game);
}
