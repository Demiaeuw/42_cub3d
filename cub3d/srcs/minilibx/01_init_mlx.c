/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:46:37 by kpourcel          #+#    #+#             */
/*   Updated: 2024/12/16 16:48:39 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	init_game_texture(t_game *game)
{
	int	i;

	game->texture = ft_calloc(5, sizeof(int *));
	if (!game->texture)
		return (print_error("Failed to allocate memory for texture array"));
	i = 0;
	while (i < 4)
	{
		if (load_texture(game, i) == -1)
		{
			free_textures(game->texture);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	load_texture(t_game *game, int index)
{
	void	*image;
	int		width;
	int		height;

	image = load_image(game, index, &width, &height);
	if (!image)
		return (-1);
	if (store_texture_data(game, index, image) == -1)
	{
		mlx_destroy_image(game->mlx, image);
		return (-1);
	}
	return (0);
}

int	store_texture_data(t_game *game, int index, void *image)
{
	int	bpp;
	int	size_line;
	int	endian;

	game->texture[index] = (int *)mlx_get_data_addr(image, &bpp,
			&size_line, &endian);
	if (!game->texture[index])
	{
		print_error("Failed to get texture data address");
		return (-1);
	}
	return (0);
}

void	*load_image(t_game *game, int index, int *width, int *height)
{
	char	*path;
	void	*image;

	path = get_texture_path(game, index);
	if (!path)
	{
		print_error("Error: Texture path is NULL");
		return (NULL);
	}
	image = mlx_xpm_file_to_image(game->mlx, path, width, height);
	if (!image)
	{
		printf("Error: Failed to load image from path: %s\n", path);
		mlx_destroy_image(game->mlx, image);
	}
	return (image);
}

char	*get_texture_path(t_game *game, int index)
{
	if (index == 0)
		return (game->infos->path_north);
	if (index == 1)
		return (game->infos->path_south);
	if (index == 2)
		return (game->infos->path_east);
	if (index == 3)
		return (game->infos->path_west);
	return (NULL);
}
