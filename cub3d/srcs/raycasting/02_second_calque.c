/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_second_calque.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:12:43 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/14 18:23:03 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	render_walls(t_game *game)
{
	int	column;

	column = 0;
	while (column < game->screen_width)
	{
		// Étape 1 : Initialisation du rayon
		init_ray(game, column);

		// Étape 2 : Initialisation des steps et distances côté
		init_step_and_side_dist(game);

		// Étape 3 : Trouve le mur avec DDA
		perform_dda(game);

		// Étape 4 : Calcul de la distance perpendiculaire
		calculate_perp_dist(game);

		// Étape 5 : Rendu de la colonne
		render_column(game, column);

		column++;
	}
}


void	calculate_perp_dist(t_game *game)
{
	if (game->dda->side == 0)
	{
		game->col_data->perp_dist = (game->dda->map_x - game->player->x 
			+ (1 - game->dda->step_x) / 2) / game->col_data->ray_dir_x;
	}
	else
	{
		game->col_data->perp_dist = (game->dda->map_y - game->player->y 
			+ (1 - game->dda->step_y) / 2) / game->col_data->ray_dir_y;
	}
}

void	perform_dda(t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (game->dda->side_dist_x < game->dda->side_dist_y)
		{
			game->dda->side_dist_x += game->dda->delta_dist_x;
			game->dda->map_x += game->dda->step_x;
			game->dda->side = 0; // Rayon touche un mur vertical
		}
		else
		{
			game->dda->side_dist_y += game->dda->delta_dist_y;
			game->dda->map_y += game->dda->step_y;
			game->dda->side = 1; // Rayon touche un mur horizontal
		}

		// Vérifie si on a touché un mur (par exemple, une case '1' dans la map)
		if (game->map->tab[game->dda->map_y][game->dda->map_x] == '1')
			hit = 1;
	}
}


void	render_column(t_game *game, int column)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;
	int	color;

	// Calcul de la hauteur de la ligne
	line_height = (int)(game->screen_height / game->col_data->perp_dist);

	// Calcul des positions de début et de fin
	draw_start = -line_height / 2 + game->screen_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + game->screen_height / 2;
	if (draw_end >= game->screen_height)
		draw_end = game->screen_height - 1;

	// Choisir une couleur pour le mur (provisoire)
	color = (game->dda->side == 0) ? 0xFFFFFF : 0xAAAAAA;

	// Dessiner la colonne dans l'image (buffer)
	y = draw_start;
	while (y <= draw_end)
	{
		*((unsigned int *)(game->addr + (y * game->line_length + column * (game->bpp / 8)))) = color;
		y++;
	}
}


void	init_ray(t_game *game, int column)
{
	float	camera_x;

	// Calcul de la position du rayon sur le plan caméra
	camera_x = 2 * ((float)column / (float)game->screen_width) - 1;

	// Direction du rayon
	game->col_data->ray_dir_x = game->player->dir_x + game->player->cam_x * camera_x;
	game->col_data->ray_dir_y = game->player->dir_y + game->player->cam_y * camera_x;

	// Position initiale dans la grille
	game->dda->map_x = (int)game->player->x;
	game->dda->map_y = (int)game->player->y;
}

void	init_step_and_side_dist(t_game *game)
{
	// Delta distances
	game->dda->delta_dist_x = fabs(1 / game->col_data->ray_dir_x);
	game->dda->delta_dist_y = fabs(1 / game->col_data->ray_dir_y);

	// Direction et distance initiale sur l'axe X
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

	// Direction et distance initiale sur l'axe Y
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
}

