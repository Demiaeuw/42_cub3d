/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_player_gestion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:15:14 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/28 17:17:48 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * - Incrémente le compteur de joueurs dans la carte.
 * - Vérifie qu'il n'y a pas plusieurs joueurs sur la carte.
 * - Met à jour la dir initiale et la position du joueur.
 * - Quitte le programme si plusieurs joueurs sont trouvés.
 */
void	update_player_position(char c, int x, int y, t_game *game)
{
	game->map->player_count++;
	if (game->map->player_count > 1)
		message_error("Multiple players found in the map", game);
	game->map->dir_start = c;
	game->map->position_start_x = x;
	game->map->position_start_y = y;
}

/**
 * - Réinitialise le compteur de joueurs à 0.
 * - Parcourt la carte pour trouver les positions de 'N', 'S', 'W', ou 'E'.
 * - Met à jour la position et la dir initiales
 * avec `update_player_position`.
 * - Vérifie qu'un joueur est présent et qu'il n'y en a pas plusieurs.
 * - Quitte le programme si aucun joueur ou plusieurs joueurs sont détectés.
 */
void	validate_and_save_player_position(t_game *game)
{
	int	x;
	int	y;

	game->map->player_count = 0;
	y = 0;
	while (game->map->tab[y] != NULL)
	{
		x = 0;
		while (game->map->tab[y][x] != '\0')
		{
			if (game->map->tab[y][x] == 'N' || game->map->tab[y][x] == 'S' ||
				game->map->tab[y][x] == 'W' || game->map->tab[y][x] == 'E')
			{
				update_player_position(game->map->tab[y][x], x, y, game);
			}
			x++;
		}
		y++;
	}
	if (game->map->player_count == 0)
		message_error("No player found in the map", game);
}

/**
 * - Initialise les coordonnées du joueur à partir de sa position de départ.
 * - Ajuste les coordonnées pour placer le joueur au centre de la case.
 * - Définit la direction initiale du joueur en fonction de 'N', 'S', 'E' ou 'W'
 */
void	player_struct_start(t_game *game)
{
	game->player->x = (float)game->map->position_start_x + 0.5;
	game->player->y = (float)game->map->position_start_y + 0.5;
	if (game->map->dir_start == 'N')
	{
		game->player->dir_x = 0.0;
		game->player->dir_y = -1.0;
	}
	else if (game->map->dir_start == 'S')
	{
		game->player->dir_x = 0.0;
		game->player->dir_y = 1.0;
	}
	else if (game->map->dir_start == 'E')
	{
		game->player->dir_x = 1.0;
		game->player->dir_y = 0.0;
	}
	else if (game->map->dir_start == 'W')
	{
		game->player->dir_x = -1.0;
		game->player->dir_y = 0.0;
	}
	player_set_fov(game->player, 66.0 * (M_PI / 180.0));
}

/**
 * @brief Initialise le plan de caméra du joueur en fonction de sa direction
 *        et du champ de vision (FOV).
 * 
 * Le plan de caméra est un vecteur perpendiculaire à la direction du joueur.
 * Sa longueur est déterminée par le FOV pour définir les limites du champ 
 * de vision. 
 * Cette fonction garantit que la caméra reste alignée avec la direction 
 * du joueur.
 * 
 * Dans l'odre : Nord, Sud, Est et Ouest
 * @param player Pointeur vers la structure du joueur, contenant sa direction
 *               et ses paramètres de caméra.
 * @param fov Champ de vision en radians, utilisé pour calculer la longueur du 
 *            plan de caméra.
 */

void	player_set_fov(t_player *player, float fov)
{
	float	cam_length;

	cam_length = tan(fov / 2.0);

	if (player->dir_x == 0 && player->dir_y == -1)
	{
		player->cam_x = cam_length;
		player->cam_y = 0.0;
	}
	else if (player->dir_x == 0 && player->dir_y == 1)
	{
		player->cam_x = -cam_length;
		player->cam_y = 0.0;
	}
	else if (player->dir_x == 1 && player->dir_y == 0)
	{
		player->cam_x = 0.0;
		player->cam_y = cam_length;
	}
	else if (player->dir_x == -1 && player->dir_y == 0)
	{
		player->cam_x = 0.0;
		player->cam_y = -cam_length;
	}
}
