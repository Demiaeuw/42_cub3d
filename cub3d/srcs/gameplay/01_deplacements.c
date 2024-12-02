/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_deplacements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:02:52 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/02 14:42:17 by kpourcel         ###   ########.fr       */
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
 * selon la dir actuelle.
 * - Se déplace latéralement à gauche (A) ou à droite (D)
 * en ajustant la dir.
 * - Utilise une vitesse de déplacement définie par `move_speed`.
 */
void	process_mouvement(t_game *game)
{
	float	move_speed;

	move_speed = 0.1;
	if (game->player->w || game->player->up)
	{
		move_player(game->player, game->player->dir_x * move_speed,
			game->player->dir_y * move_speed);
		printf("le player avance\n");
	}
	if (game->player->s || game->player->down)
	{
		move_player(game->player, -game->player->dir_x * move_speed,
			-game->player->dir_y * move_speed);
		printf("le player recul\n");
	}
	if (game->player->a)
	{
		move_player(game->player, -game->player->dir_y * move_speed,
			game->player->dir_x * move_speed);
		printf("le player straff a gauche\n");
	}
	if (game->player->d)
	{
		move_player(game->player, game->player->dir_y * move_speed,
			-game->player->dir_x * move_speed);
		printf("le player straffe a droite\n");
	}
}
