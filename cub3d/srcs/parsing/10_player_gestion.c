/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_player_gestion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:15:14 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/07 17:00:06 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	update_player_position(char c, int x, int y, t_map *map)
{
	map->player_count++;
	if (map->player_count > 1)
		message_error("Multiple players found in the map");
	map->direction_start = c;
	map->position_start_x = x;
	map->position_start_y = y;
}

void	validate_and_save_player_position(t_map *map)
{
	int	x;
	int	y;

	map->player_count = 0;
	y = 0;
	while (map->tab[y] != NULL)
	{
		x = 0;
		while (map->tab[y][x] != '\0')
		{
			if (map->tab[y][x] == 'N' || map->tab[y][x] == 'S' ||
				map->tab[y][x] == 'W' || map->tab[y][x] == 'E')
			{
				update_player_position(map->tab[y][x], x, y, map);
			}
			x++;
		}
		y++;
	}
	if (map->player_count == 0)
		message_error("No player found in the map");
}

void	player_struct_start(t_game *game)
{
	game->player->x = (float)game->map->position_start_x + 0.5;
	game->player->y = (float)game->map->position_start_y + 0.5;

	if (game->map->direction_start == 'N')
	{
		game->player->direction_x = 0.0;
		game->player->direction_y = -1.0;
	}
	else if (game->map->direction_start == 'S')
	{
		game->player->direction_x = 0.0;
		game->player->direction_y = 1.0;
	}
	else if (game->map->direction_start == 'E')
	{
		game->player->direction_x = 1.0;
		game->player->direction_y = 0.0;
	}
	else if (game->map->direction_start == 'W')
	{
		game->player->direction_x = -1.0;
		game->player->direction_y = 0.0;
	}
}

