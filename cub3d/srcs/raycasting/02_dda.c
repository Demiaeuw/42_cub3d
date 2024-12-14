/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 02:37:46 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/14 03:16:10 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	perform_dda(t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		// Avance dans la direction ayant la plus petite distance côté
		if (game->dda->side_dist_x < game->dda->side_dist_y)
		{
			game->dda->side_dist_x += game->dda->delta_dist_x;
			game->dda->map_x += game->dda->step_x;
			game->dda->side = 0; // Mur vertical
		}
		else
		{
			game->dda->side_dist_y += game->dda->delta_dist_y;
			game->dda->map_y += game->dda->step_y;
			game->dda->side = 1; // Mur horizontal
		}

		// Vérifie si le rayon touche un mur
		if (game->map->tab[game->dda->map_y][game->dda->map_x] == '1')
			hit = 1;

		// Debug pour chaque étape du DDA
		// printf("DDA Step: Map (%d, %d), Side: %d\n",
		// 	game->dda->map_x, game->dda->map_y, game->dda->side);
	}
}

void	calculate_perp_dist(t_game *game)
{
	float	perp_dist;

	if (game->dda->side == 0) // Mur vertical
		perp_dist = (game->dda->map_x - game->player->x 
				+ (1 - game->dda->step_x) / 2) / game->col_data->ray_dir_x;
	else // Mur horizontal
		perp_dist = (game->dda->map_y - game->player->y 
				+ (1 - game->dda->step_y) / 2) / game->col_data->ray_dir_y;

	// Stocker la distance dans une variable pour l'affichage
	game->col_data->perp_dist = perp_dist;

	// printf("Column %d: Perpendicular Distance = %f\n",
	// 	game->col_data->column, perp_dist);
}

