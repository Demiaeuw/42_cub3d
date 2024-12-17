/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:26:02 by kpourcel          #+#    #+#             */
/*   Updated: 2024/12/17 15:27:11 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	free_images(void *mlx, void **images, int size)
{
	int	i;

	i = 0;
	if (!images)
		return ;
	while (i < size)
	{
		if (images[i])
		{
			mlx_destroy_image(mlx, images[i]);
			images[i] = NULL;
		}
		i++;
	}
	free(images);
	images = NULL;
}

void	free_infos(t_info *infos)
{
	if (!infos)
		return ;
	free(infos->path_north);
	free(infos->path_south);
	free(infos->path_east);
	free(infos->path_west);
	free(infos);
}

void	free_window_and_display(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	cleanup_resources(t_game *game)
{
	if (!game)
		return ;
	if (game->image_struct)
		free_images(game->mlx, (void **)game->image_struct, 4);
	if (game->infos)
		free_infos(game->infos);
	if (game->map)
	{
		free_map_tab(game->map);
		free(game->map);
	}
	if (game->player)
		free(game->player);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	free_window_and_display(game);
}
