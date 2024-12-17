/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:46:37 by kpourcel          #+#    #+#             */
/*   Updated: 2024/12/17 15:52:17 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	init_game_texture(t_game *game)
{
	return (load_all_textures(game));
}

int	allocate_texture_resources(t_game *game)
{
	game->texture = ft_calloc(4, sizeof(int *));
	game->image_struct = ft_calloc(4, sizeof(void *));
	if (!game->texture || !game->image_struct)
		return (print_error("Failed to allocate memory textures or images"));
	return (0);
}

int	load_single_texture(t_game *game, char *path, int index)
{
	int		bpp;
	int		size_line;
	int		endian;

	if (!path)
		return (print_error("Error: Texture path is NULL"));
	game->image_struct[index] = mlx_xpm_file_to_image(game->mlx, path, \
		&(int){0}, &(int){0});
	if (!game->image_struct[index])
		return (print_error("Failed to load texture image"));
	game->texture[index] = (int *)mlx_get_data_addr(game->image_struct[index], \
		&bpp, &size_line, &endian);
	if (!game->texture[index])
	{
		mlx_destroy_image(game->mlx, game->image_struct[index]);
		game->image_struct[index] = NULL;
		return (print_error("Failed to get texture data address"));
	}
	return (0);
}

int	load_all_textures(t_game *game)
{
	int		i;
	char	*paths[4];

	paths[0] = game->infos->path_north;
	paths[1] = game->infos->path_south;
	paths[2] = game->infos->path_east;
	paths[3] = game->infos->path_west;
	if (allocate_texture_resources(game) == -1)
		return (-1);
	i = 0;
	while (i < 4)
	{
		if (load_single_texture(game, paths[i], i) == -1)
			return (-1);
		i++;
	}
	return (0);
}
