/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 02:30:34 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/14 03:13:59 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	render(void *param)
{
	t_game	*game;

	game = (t_game *)param;

	// Gère les mouvements du joueur
	process_mouvement(game);

	// Efface l'écran avant de redessiner
	mlx_clear_window(game->mlx, game->win);

	// Appelle le raycasting pour dessiner les murs
	raycasting(game);

	return (0); // Retourne 0 pour indiquer le succès
}


void	raycasting(t_game *game)
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
		render_column(game, column, game->col_data->perp_dist, game->dda->side);

		column++;
	}
}

