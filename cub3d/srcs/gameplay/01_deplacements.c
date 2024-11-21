/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_deplacements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:02:52 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/21 05:28:20 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * - Déplace le joueur en ajustant ses coordonnées X et Y.
 * - Ajoute `delta_x` à la position X.
 * - Ajoute `delta_y` à la position Y.
 */
void	move_player(t_player *player, float delta_x, float delta_y)
{
	player->x += delta_x;
	player->y += delta_y;
}

/**
 * - Gère le déplacement du joueur en fonction de la touche pressée.
 * - Se déplace vers l'avant (W/UP) ou vers l'arrière (S/DOWN)
 * selon la direction actuelle.
 * - Se déplace latéralement à gauche (A) ou à droite (D)
 * en ajustant la direction.
 * - Utilise une vitesse de déplacement définie par `move_speed`.
 */
void	handle_movement(int keycode, t_game *game)
{
	float	move_speed;

	move_speed = 0.1;
	if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game->player, game->player->direction_x * move_speed,
			game->player->direction_y * move_speed);
	else if (keycode == 'S' || keycode == KEY_DOWN)
		move_player(game->player, -game->player->direction_x * move_speed,
			-game->player->direction_y * move_speed);
	else if (keycode == 'A')
		move_player(game->player, -game->player->direction_y * move_speed,
			game->player->direction_x * move_speed);
	else if (keycode == 'D')
		move_player(game->player, game->player->direction_y * move_speed,
			-game->player->direction_x * move_speed);
}
