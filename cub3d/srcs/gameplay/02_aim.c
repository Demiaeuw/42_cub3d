/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_aim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:06:44 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/02 14:42:35 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * - Fait pivoter la caméra du joueur en modifiant sa dir.
 * - Applique une rotation à l'aide d'un angle donné.
 * - Calcule la nouvelle dir X et Y à l'aide des formules trigonométriques
 *   (cosinus et sinus).
 */
void	rotate_camera(t_player *player, float angle)
{
	float	old_dir_x;
	float	rotation_speed;

	rotation_speed = angle;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rotation_speed)
		- player->dir_y * sin(rotation_speed);
	player->dir_y = old_dir_x * sin(rotation_speed)
		+ player->dir_y * cos(rotation_speed);
}

/**
 * - Gère la rotation de la caméra en fonction des touches fléchées.
 * - Fait pivoter la caméra vers la gauche (KEY_LEFT) avec un angle négatif.
 * - Fait pivoter la caméra vers la droite (KEY_RIGHT) avec un angle positif.
 * - Utilise une vitesse de rotation définie par `rotation_speed`.
 */
void	handle_camera_rotation(t_game *game)
{
	float	rotation_speed;

	rotation_speed = 0.05;
	if (game->player->left)
		rotate_camera(game->player, -rotation_speed);
	else if (game->player->right)
		rotate_camera(game->player, rotation_speed);
}
