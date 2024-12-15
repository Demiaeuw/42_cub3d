/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_premier_calque.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:29:14 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/15 20:56:17 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	init_image(t_game *game)
{
	game->img = mlx_new_image(game->mlx, game->screen_width,
			game->screen_height);
	if (!game->img)
	{
		fprintf(stderr, "Error: Failed to create image.\n");
		cleanup_and_exit(game);
		exit(EXIT_FAILURE);
	}
	game->addr = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_length, &game->endian);
	if (!game->addr)
	{
		fprintf(stderr, "Error: Failed to get image address.\n");
		cleanup_and_exit(game);
		exit(EXIT_FAILURE);
	}
	printf("Image initialized successfully: Address = %p, BPP = %d, Line Length = %d, Endian = %d\n",
		game->addr, game->bpp, game->line_length, game->endian); // a delete 
}

void	draw_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->screen_height / 2)
	{
		x = 0;
		while (x < game->screen_width)
		{
			*((unsigned int *)(game->addr + (y * game->line_length \
				+ x * (game->bpp / 8)))) = game->map->color_ceiling;
			x++;
		}
		y++;
	}
}

void	draw_floor(t_game *game)
{
	int	x;
	int	y;

	y = game->screen_height / 2;
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			*((unsigned int *)(game->addr + (y * game->line_length \
			+ x * (game->bpp / 8)))) = game->map->color_floor;
			x++;
		}
		y++;
	}
}

void	draw_floor_and_ceiling(t_game *game)
{
	draw_ceiling(game);
	draw_floor(game);
}
