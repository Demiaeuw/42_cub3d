/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:04 by kpourcel          #+#    #+#             */
/*   Updated: 2024/12/03 01:48:03 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * @brief Parcourt chaque colonne de l'écran pour effectuer le raycasting.
 *        Calcule la direction du rayon pour chaque colonne en fonction 
 *        de la caméra et appelle le traitement d'un rayon unique.
 * 
 * @param game Pointeur vers la structure principale du jeu.
 */
void	raycasting(t_game *game)
{
	int		column;
	float	camera_x;
	float	ray_dir_x;
	float	ray_dir_y;

	column = 0;
	while (column < game->screen_width)
	{
		camera_x = 2 * ((float)column / (float)game->screen_width) - 1;
		ray_dir_x = game->player->dir_x + game->player->cam_x * camera_x;
		ray_dir_y = game->player->dir_y + game->player->cam_y * camera_x;
		cast_single_ray(game, ray_dir_x, ray_dir_y);
		column++;
	}
}

/**
 * @brief Initialise les variables nécessaires pour l'algorithme DDA,
 *        notamment les positions dans la grille et les distances delta.
 * 
 * @param game Pointeur vers la structure principale du jeu.
 * @param ray_dir_x Direction du rayon sur l'axe X.
 * @param ray_dir_y Direction du rayon sur l'axe Y.
 * @param dda Pointeur vers la structure DDA pour stocker les données calculées.
 */

void	set_dda(t_game *game, float ray_dir_x, float ray_dir_y)
{
	game->dda->map_x = (int)game->player->x;
	game->dda->map_y = (int)game->player->y;
	game->dda->delta_dist_x = fabs(1 / ray_dir_x);
	game->dda->delta_dist_y = fabs(1 / ray_dir_y);
}

/**
 * @brief Exécute l'algorithme DDA pour trouver l'intersection avec un mur.
 *        Parcourt la grille jusqu'à rencontrer une case contenant un mur.
 * 
 * @param game Pointeur vers la structure principale du jeu.
 * @param dda Pointeur vers la structure DDA contenant 
 * les données d'intersection.
 */

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
			game->dda->side = 0;
		}
		else
		{
			game->dda->side_dist_y += game->dda->delta_dist_y;
			game->dda->map_y += game->dda->step_y;
			game->dda->side = 1;
		}
		if (game->map->tab[game->dda->map_x][game->dda->map_y] > 0)
			hit = 1;
	}
}

/**
 * @brief Traite un rayon unique en effectuant toutes les étapes :
 *        initialisation, calcul des étapes, exécution de DDA et rendu.
 * 
 * @param game Pointeur vers la structure principale du jeu.
 * @param ray_dir_x Direction du rayon sur l'axe X.
 * @param ray_dir_y Direction du rayon sur l'axe Y.
 * @param column Numéro de la colonne correspondante au rayon.
 */

void	cast_single_ray(t_game *game, float ray_dir_x, float ray_dir_y)
{
	set_dda(game, ray_dir_x, ray_dir_y);
	printf("\n\n\n");					// a delete pour affichage de test
	print_col_info(game->col_data);		// a delete pour affichage de test
	calculate_steps(game, ray_dir_x, ray_dir_y);
	perform_dda(game);
	calculate_perp_dist(game);
}

/**
 * @brief Dessine une ligne verticale sur une image ou une fenêtre.
 * 
 * @param x Position X de la colonne.
 * @param start Position Y de départ de la ligne.
 * @param end Position Y de fin de la ligne.
 * @param color Couleur de la ligne (format hexadécimal).
 */
// void	vertical_line(int x, int start, int end, int color)
// {
// 	t_game	*game;
// 	int		y;

// 	if (start < 0)
// 		start = 0;
// 	if (end >= game->screen_height)
// 		end = game->screen_height - 1;
// 	y = start;
// 	while (y <= end)
// 	{
// 		mlx_xpm_file_to_image(game, x, y, color);
// 		y++;
// 	}
// }
