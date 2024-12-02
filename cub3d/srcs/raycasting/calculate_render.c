/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:10:51 by kpourcel          #+#    #+#             */
/*   Updated: 2024/12/03 00:40:17 by kpourcel         ###   ########.fr       */
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
void	calculate_perp_dist(t_game *game, t_dda *dda, t_column_data *col_data)
{
	float	perp_dist;

	if (dda->side == 0)
		perp_dist = (dda->map_x - game->player->x
				+ (1 - dda->step_x) / 2) / col_data->ray_dir_x;
	else
		perp_dist = (dda->map_y - game->player->y
				+ (1 - dda->step_y) / 2) / col_data->ray_dir_y;
	render_column(game, col_data->column, perp_dist, dda->side);
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
	int	color;

	line_height = (int)(game->screen_height / perp_dist);
	draw_start = -line_height / 2 + game->screen_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + game->screen_height / 2;
	if (draw_end >= game->screen_height)
		draw_end = game->screen_height - 1;
	if (side == 0)
		color = 0xFFFFFF;
	else
		color = 0xAAAAAA;
	vertical_line(column, draw_start, draw_end, color);
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
void	calculate_steps(t_game *game, float ray_dir_x, float ray_dir_y,
	t_dda *dda)
{
	if (ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (game->player->x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - game->player->x)
			* dda->delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (game->player->y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - game->player->y)
			* dda->delta_dist_y;
	}
}
