/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_aim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:06:44 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/21 05:29:21 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * - Fait pivoter la caméra du joueur en modifiant sa direction.
 * - Applique une rotation à l'aide d'un angle donné.
 * - Calcule la nouvelle direction X et Y à l'aide des formules trigonométriques
 *   (cosinus et sinus).
 */
void	rotate_camera(t_player *player, float angle)
{
	float	old_dir_x;
	float	rotation_speed;

	rotation_speed = angle;
	old_dir_x = player->direction_x;
	player->direction_x = player->direction_x * cos(rotation_speed)
		- player->direction_y * sin(rotation_speed);
	player->direction_y = old_dir_x * sin(rotation_speed)
		+ player->direction_y * cos(rotation_speed);
}

/**
 * - Gère la rotation de la caméra en fonction des touches fléchées.
 * - Fait pivoter la caméra vers la gauche (KEY_LEFT) avec un angle négatif.
 * - Fait pivoter la caméra vers la droite (KEY_RIGHT) avec un angle positif.
 * - Utilise une vitesse de rotation définie par `rotation_speed`.
 */
void	handle_camera_rotation(int keycode, t_game *game)
{
	float	rotation_speed;

	rotation_speed = 0.05;
	if (keycode == KEY_LEFT)
		rotate_camera(game->player, -rotation_speed);
	else if (keycode == KEY_RIGHT)
		rotate_camera(game->player, rotation_speed);
}
