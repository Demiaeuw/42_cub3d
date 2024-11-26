/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_init_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:32:15 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/26 13:31:48 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * Initialise la structure `t_info` pour stocker les chemins des textures.
 * Toutes les valeurs des chemins sont initialisées à NULL.
 * Retourne un pointeur vers la structure initialisée ou NULL en cas d'échec.
 */

t_info	*init_info(void)
{
	t_info	*infos;

	infos = (t_info *)malloc(sizeof(t_info));
	if (!infos)
		return (NULL);
	infos->path_north = NULL;
	infos->path_south = NULL;
	infos->path_east = NULL;
	infos->path_west = NULL;
	return (infos);
}


/**
 * Initialise la structure `t_map` pour stocker les informations de la carte.
 * Les valeurs par défaut sont définies (NULL pour `tab`, -1 pour les couleurs,
 * et des valeurs invalides pour les positions).
 * Retourne un pointeur vers la structure initialisée ou NULL en cas d'échec.
 */

t_map	*init_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->tab = NULL;
	map->height = 0;
	map->color_floor = -1;
	map->color_ceiling = -1;
	map->direction_start = '\0';
	map->position_start_x = -1;
	map->position_start_y = -1;
	map->player_count = 0;
	return (map);
}

/**
 * Initialise la structure `t_player` pour stocker les informations du joueur.
 * Position initiale (x, y) définie à 0.0 et la direction à (1.0, 0.0).
 * Retourne un pointeur vers la structure initialisée ou affiche une erreur
 * en cas d'échec d'allocation mémoire.
 */
t_player	*init_player(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
	{
		message_error("allocation mémoire pour le joueur", NULL);
		return (NULL);
	}
	player->x = 0.0;
	player->y = 0.0;
	player->direction_x = 1.0;
	player->direction_y = 0.0;
	return (player);
}

/**
 * Initialise la structure `t_game` qui contient toutes les données du jeu,
 * incluant les informations de texture (`t_info`), la carte (`t_map`),
 * et le joueur (`t_player`). Vérifie que chaque sous-structure est correctement
 * allouée et initialise également MinilibX et la fenêtre. En cas d'erreur
 * d'initialisation ou d'allocation, libère les ressources et retourne NULL.
 */
t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->infos = init_info();
	game->map = init_map();
	game->player = init_player();
	game->texture = NULL; // a free
	if (!game->infos || !game->map || !game->player)
	{
		cleanup_and_exit(game);
		return (NULL);
	}
	if (init_mlx_and_window(game) == -1)
	{
		cleanup_and_exit(game);
		return (NULL);
	}
	return (game);
}
