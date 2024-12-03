/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_init_game1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:32:15 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/03 15:53:14 by acabarba         ###   ########.fr       */
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
	map->dir_start = '\0';
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
	player->dir_x = 1.0;
	player->dir_y = 0.0;
	player->cam_x = 0.0;
	player->cam_y = 0.0;
	player->w = 0;
	player->a = 0;
	player->s = 0;
	player->d = 0;
	player->up = 0;
	player->left = 0;
	player->down = 0;
	player->right = 0;
	return (player);
}

/**
 * Initialise la structure `t_dda` pour stocker les données nécessaires
 * au calcul du Digital Differential Analysis (DDA).
 * Les valeurs par défaut sont définies à zéro pour les coordonnées,
 * les distances et les étapes, garantissant un état initial neutre.
 * Retourne un pointeur vers la structure initialisée ou affiche une erreur
 * en cas d'échec d'allocation mémoire.
 */
t_dda	*init_dda(void)
{
	t_dda	*dda;

	dda = malloc(sizeof(t_dda));
	if (!dda)
	{
		message_error("allocation mémoire pour DDA", NULL);
		return (NULL);
	}
	dda->map_x = 0;
	dda->map_y = 0;
	dda->delta_dist_x = 0;
	dda->delta_dist_y = 0;
	dda->step_x = 0;
	dda->step_y = 0;
	dda->side_dist_x = 0.0;
	dda->side_dist_y = 0.0;
	dda->side = 0;
	return (dda);
}

/**
 * Initialise la structure `t_col_data` pour stocker
 * les informations d'une colonne
 * dans le contexte du raycasting.
 * Les valeurs initiales définissent la colonne à 0 et les
 * composantes directionnelles
 * du rayon à 0.0, garantissant un état initial neutre.
 * Retourne un pointeur vers la structure initialisée ou affiche une erreur
 * en cas d'échec d'allocation mémoire.
 */
t_col_data	*init_col_data(void)
{
	t_col_data	*col_data;

	col_data = malloc(sizeof(t_col_data));
	if (!col_data)
	{
		message_error("allocation mémoire pour la colonne", NULL);
		return (NULL);
	}
	col_data->column = 0;
	col_data->ray_dir_x = 0.0;
	col_data->ray_dir_y = 0.0;
	return (col_data);
}
