/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_rayon.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 02:33:15 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/14 03:15:56 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	init_ray(t_game *game, int column)
{
	float	camera_x; // Position du rayon sur le plan caméra
	float	ray_dir_x;
	float	ray_dir_y;

	// 1. Calcule la direction du rayon
	camera_x = 2 * ((float)column / (float)game->screen_width) - 1;
	ray_dir_x = game->player->dir_x + game->player->cam_x * camera_x;
	ray_dir_y = game->player->dir_y + game->player->cam_y * camera_x;

	// Stocker les données dans `t_col_data`
	game->col_data->ray_dir_x = ray_dir_x;
	game->col_data->ray_dir_y = ray_dir_y;

	// 2. Initialisation de la position dans la grille
	game->dda->map_x = (int)game->player->x;
	game->dda->map_y = (int)game->player->y;

	// 3. Calcul des distances delta
	if (ray_dir_x != 0)
		game->dda->delta_dist_x = fabs(1 / ray_dir_x);
	else
		game->dda->delta_dist_x = INFINITY;
	if (ray_dir_y != 0)
		game->dda->delta_dist_y = fabs(1 / ray_dir_y);
	else
		game->dda->delta_dist_y = INFINITY;

	// printf("Column %d: Ray Dir (%f, %f), Delta Dist (%f, %f)\n",
	// 	column, ray_dir_x, ray_dir_y, game->dda->delta_dist_x, game->dda->delta_dist_y);
}

void	init_step_and_side_dist(t_game *game)
{
	// 1. Déterminer le step et la première distance côté en X
	if (game->col_data->ray_dir_x < 0)
	{
		game->dda->step_x = -1;
		game->dda->side_dist_x = (game->player->x - game->dda->map_x) * game->dda->delta_dist_x;
	}
	else
	{
		game->dda->step_x = 1;
		game->dda->side_dist_x = (game->dda->map_x + 1.0 - game->player->x) * game->dda->delta_dist_x;
	}

	// 2. Déterminer le step et la première distance côté en Y
	if (game->col_data->ray_dir_y < 0)
	{
		game->dda->step_y = -1;
		game->dda->side_dist_y = (game->player->y - game->dda->map_y) * game->dda->delta_dist_y;
	}
	else
	{
		game->dda->step_y = 1;
		game->dda->side_dist_y = (game->dda->map_y + 1.0 - game->player->y) * game->dda->delta_dist_y;
	}

	// printf("Steps: Step X = %d, Step Y = %d, Side Dist (%f, %f)\n",
	// 	game->dda->step_x, game->dda->step_y, game->dda->side_dist_x, game->dda->side_dist_y);
}

void	render_column(t_game *game, int column, float perp_dist, int side)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;

	// Calcul de la hauteur de la ligne
	line_height = (int)(game->screen_height / perp_dist);

	// Calcul des positions de début et de fin
	draw_start = -line_height / 2 + game->screen_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + game->screen_height / 2;
	if (draw_end >= game->screen_height)
		draw_end = game->screen_height - 1;

	// Choisir la couleur en fonction du côté touché
	if (side == 0) // Mur vertical
		color = 0xFFFFFF; // Blanc
	else // Mur horizontal
		color = 0xAAAAAA; // Gris

	// Dessiner la ligne verticale
	for (int y = draw_start; y <= draw_end; y++)
		mlx_pixel_put(game->mlx, game->win, column, y, color);
}


