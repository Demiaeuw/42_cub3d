/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_deplacements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:02:52 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/16 17:19:28 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * Fonction qui peret de verifier les colisions avec les murs
 * return 0 quand c'est une limite de map ou un mur
 * sinon return 1
 */

int can_move_to(char **map, float new_x, float new_y) {
    int map_x1, map_x2, map_y1, map_y2;

    // Vérifie les coins du joueur avec la marge (padding)
    map_x1 = (int)(new_x - PADDING);
    map_x2 = (int)(new_x + PADDING);
    map_y1 = (int)(new_y - PADDING);
    map_y2 = (int)(new_y + PADDING);

    // Si l'un des coins touche un mur ('1'), le mouvement est bloqué
    if (map[map_y1][map_x1] == '1' || map[map_y1][map_x2] == '1' ||
        map[map_y2][map_x1] == '1' || map[map_y2][map_x2] == '1') {
        return 0;
    }
    return 1;
}

void	move_player(t_game *game, float delta_x, float delta_y)
{
	float new_x;
	float new_y;

	new_x = game->player->x + delta_x;
	new_y = game->player->y + delta_y;
	if (can_move_to(game->map->tab, new_x, new_y))
	{
		game->player->x += delta_x;
		game->player->y += delta_y;
	}
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

	move_speed = 0.01;
	if (game->player->w || game->player->up)
		move_player(game, game->player->dir_x * move_speed,
			game->player->dir_y * move_speed);
	if (game->player->s || game->player->down)
		move_player(game, -game->player->dir_x * move_speed,
			-game->player->dir_y * move_speed);
	if (game->player->a)
		move_player(game, game->player->dir_y * move_speed,
			-game->player->dir_x * move_speed);
	if (game->player->d)
		move_player(game, -game->player->dir_y * move_speed,
			game->player->dir_x * move_speed);
}
