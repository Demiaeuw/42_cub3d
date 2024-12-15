/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_deplacements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:02:52 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/15 20:00:50 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * Fonction qui peret de verifier les colisions avec les murs
 * return 0 quand c'est une limite de map ou un mur
 * sinon return 1
 */
int	can_move_to(char **map, float new_x, float new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;

	printf("Checking position: (%d, %d)\n", map_x, map_y);						// a delete pour test
	if (map[map_y][map_x] == '1')
	{
		printf("Collision at: (%d, %d)\n", map_x, map_y);						// a delete pour test
		return (0);
	}
	return (1);
}

/**
 * - Déplace le joueur en ajustant ses coordonnées X et Y.
 * - Ajoute `delta_x` à la position X.
 * - Ajoute `delta_y` à la position Y.
 */
void	move_player(t_game *game, float delta_x, float delta_y)
{
	float	new_x;
	float	new_y;

	new_x = game->player->x + delta_x;
	new_y = game->player->y + delta_y;

	printf("Trying to move to: (%f, %f)\n", new_x, new_y);
	if (can_move_to(game->map->tab, new_x, new_y))
	{
		game->player->x += delta_x;
		game->player->y += delta_y;
		printf("Move successful to: (%f, %f)\n", game->player->x, game->player->y);	// a delete pour test
	}
	else
	{
		printf("Collision détectée : impossible de se déplacer\n");				// a delete pour test
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
	{
		move_player(game, game->player->dir_x * move_speed,
			game->player->dir_y * move_speed);
		printf("le player avance\n");			// pour test a delete
	}
	if (game->player->s || game->player->down)
	{
		move_player(game, -game->player->dir_x * move_speed,
			-game->player->dir_y * move_speed);
		printf("le player recul\n");			// pour test a delete
	}
	if (game->player->a) // strafe à gauche
	{
		move_player(game, game->player->dir_y * move_speed,
			-game->player->dir_x * move_speed);
		printf("le player straff a gauche\n");	// pour test a delete
	}
	if (game->player->d) // strafe à droite
	{
		move_player(game, -game->player->dir_y * move_speed,
			game->player->dir_x * move_speed);
		printf("le player straffe a droite\n");	// pour test a delete
	} 
}
