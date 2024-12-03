/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_deplacements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:02:52 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/03 15:33:22 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * Fonction qui peret de verifier les colisions avec les murs
 * return 0 quand c'est une limite de map ou un mur
 * sinon return 1
 */
int	can_move_to(t_map *map, float new_x, float new_y)
{
	int	grid_x;
	int	grid_y;
	
	grid_x = (int)new_x;
	grid_y = (int)new_y;
	if (grid_x < 0 || grid_x >= map->height || grid_y < 0
		|| grid_y >= (int)ft_strlen(map->tab[grid_x]))
		return (0);
	if (map->tab[grid_x][grid_y] == '1')
		return (0);
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
	if (can_move_to(game->map, new_x, new_y))
	{
		game->player->x += delta_x;
		game->player->y += delta_y;	
	}
	else																		// pour test
		printf("Collision détectée : impossible de se déplacer\n");				// a delete
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
	if (game->player->a)
	{
		move_player(game, -game->player->dir_y * move_speed,
			game->player->dir_x * move_speed);
		printf("le player straff a gauche\n");	// pour test a delete
	}
	if (game->player->d)
	{
		move_player(game, game->player->dir_y * move_speed,
			-game->player->dir_x * move_speed);
		printf("le player straffe a droite\n");	// pour test a delete
	} 
}
