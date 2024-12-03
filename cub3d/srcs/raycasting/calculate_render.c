/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:10:51 by kpourcel          #+#    #+#             */
/*   Updated: 2024/12/03 01:37:47 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * @brief Calcule la distance perpendiculaire entre le joueur et un mur.
 *        Utilise les coordonnées des rayons et le DDA pour déterminer 
 *        la distance exacte au mur, puis appelle le rendu de la colonne.
 * 
 * @param game Pointeur vers la structure principale du jeu.
 * @param dda Pointeur vers la structure DDA contenant les données 
 * d'intersection.
 * @param col_data Pointeur vers la structure contenant les données 
 * du rayon actuel
 */
void	calculate_perp_dist(t_game *game)
{
	float	perp_dist;

	if (game->dda->side == 0)
		perp_dist = (game->dda->map_x - game->player->x
				+ (1 - game->dda->step_x) / 2) / game->col_data->ray_dir_x;
	else
		perp_dist = (game->dda->map_y - game->player->y
				+ (1 - game->dda->step_y) / 2) / game->col_data->ray_dir_y;
	render_column(game, game->col_data->column, perp_dist, game->dda->side);
}

/**
 * @brief Calcule et dessine une colonne de l'écran correspondant à un mur.
 *        La hauteur de la colonne est déterminée par la distance au mur.
 *        Applique une couleur différente selon que le mur est frappé 
 *        horizontalement ou verticalement.
 * 
 * @param game Pointeur vers la structure principale du jeu.
 * @param column Numéro de la colonne en cours de rendu (position X sur l'écran).
 * @param perp_dist Distance perpendiculaire calculée jusqu'au mur.
 * @param side Indique si le mur est frappé horizontalement (1) 
 * ou verticalement (0).
 */

void	render_column(t_game *game, int column, float perp_dist, int side)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	// int	color;

	(void)column;
	(void)side;
	line_height = (int)(game->screen_height / perp_dist);
	draw_start = -line_height / 2 + game->screen_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + game->screen_height / 2;
	if (draw_end >= game->screen_height)
		draw_end = game->screen_height - 1;
	// if (side == 0)
	// 	color = 0xFFFFFF;
	// else
	// 	color = 0xAAAAAA;
	// vertical_line(column, draw_start, draw_end, color);
}

/**
 * @brief Calcule les étapes nécessaires pour parcourir la grille avec DDA.
 *        Initialise les distances latérales et les directions (steps).
 * 
 * @param game Pointeur vers la structure principale du jeu.
 * @param ray_dir_x Direction du rayon sur l'axe X.
 * @param ray_dir_y Direction du rayon sur l'axe Y.
 * @param dda Pointeur vers la structure DDA pour stocker 
 * les étapes et distances.
 */
void	calculate_steps(t_game *game, float ray_dir_x, float ray_dir_y)
{
	if (ray_dir_x < 0)
	{
		game->dda->step_x = -1;
		game->dda->side_dist_x = (game->player->x - game->dda->map_x) * game->dda->delta_dist_x;
	}
	else
	{
		game->dda->step_x = 1;
		game->dda->side_dist_x = (game->dda->map_x + 1.0 - game->player->x)
			* game->dda->delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		game->dda->step_y = -1;
		game->dda->side_dist_y = (game->player->y - game->dda->map_y) * game->dda->delta_dist_y;
	}
	else
	{
		game->dda->step_y = 1;
		game->dda->side_dist_y = (game->dda->map_y + 1.0 - game->player->y)
			* game->dda->delta_dist_y;
	}
}
