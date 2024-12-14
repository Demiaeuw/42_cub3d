/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_premier_calque.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:29:14 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/15 19:36:37 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	init_image(t_game *game)
{
	// Création de l'image
	game->img = mlx_new_image(game->mlx, game->screen_width, game->screen_height);
	if (!game->img)
	{
		fprintf(stderr, "Error: Failed to create image.\n");
		cleanup_and_exit(game);
		exit(EXIT_FAILURE);
	}

	// Récupération de l'adresse mémoire de l'image
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_length, &game->endian);
	if (!game->addr)
	{
		fprintf(stderr, "Error: Failed to get image address.\n");
		cleanup_and_exit(game);
		exit(EXIT_FAILURE);
	}

	// Debugging
	printf("Image initialized successfully: Address = %p, BPP = %d, Line Length = %d, Endian = %d\n",
		game->addr, game->bpp, game->line_length, game->endian);
}



void	draw_floor_and_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->screen_height / 2) // Plafond
	{
		x = 0;
		while (x < game->screen_width)
		{
			*((unsigned int *)(game->addr + (y * game->line_length + x * (game->bpp / 8)))) =
				game->map->color_ceiling;
			x++;
		}
		y++;
	}
	while (y < game->screen_height) // Sol
	{
		x = 0;
		while (x < game->screen_width)
		{
			*((unsigned int *)(game->addr + (y * game->line_length + x * (game->bpp / 8)))) =
				game->map->color_floor;
			x++;
		}
		y++;
	}
}
