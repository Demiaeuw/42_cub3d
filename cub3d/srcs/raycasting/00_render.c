/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 02:30:34 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/14 20:32:59 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	render(void *param)
{
	t_game	*game;

	game = (t_game *)param;

	// Gère les mouvements du joueur
	process_mouvement(game);

	// Gère la rotation de la caméra
	handle_camera_rotation(game);

	// Dessiner le premier calque (plafond + sol)
	draw_floor_and_ceiling(game);

	// // Dessiner les murs par-dessus
	render_walls(game);

	printf("  Position X: %.2f\n", game->player->x);
	printf("  Position Y: %.2f\n", game->player->y);

	// // Afficher l'image dans la fenêtre
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

	return (0);
}
