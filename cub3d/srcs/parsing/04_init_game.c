/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_init_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:32:15 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/07 16:52:19 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

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

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->infos = init_info();
	game->map = init_map();
	game->player = init_player();
	if (!game->infos || !game->map || !game->player)
	{
		free(game->infos);
		free(game->map);
		free(game->player);
		free(game);
		return (NULL);
	}
	return (game);
}

t_player	*init_player(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
	{
		message_error("allocation mémoire pour le joueur");
		return (NULL);
	}
	player->x = 0.0;
	player->y = 0.0;
	player->direction_x = 1.0;
	player->direction_y = 0.0;
	return (player);
}
