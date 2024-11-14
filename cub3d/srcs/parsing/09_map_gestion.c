/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_map_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:43 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/14 19:52:41 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	check_map_surrounded_by_walls(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map->tab[y] != NULL)
	{
		x = 0;
		while (game->map->tab[y][x] != '\0')
		{
			if (game->map->tab[y][x] == '0' || game->map->tab[y][x] == 'N'
				|| game->map->tab[y][x] == 'S' || game->map->tab[y][x] == 'E'
				|| game->map->tab[y][x] == 'W')
				check_adjacent(game->map->tab, x, y, game->map->height);
			x++;
		}
		y++;
	}
}

int	is_player_character(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int	is_valid_adjacent(char c)
{
	return (c == '0' || c == '1');
}

void	check_player_position(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map->tab[y] != NULL)
	{
		x = 0;
		while (game->map->tab[y][x] != '\0')
		{
			if (is_player_character(game->map->tab[y][x]))
			{
				if (y == 0 || y == game->map->height - 1 || x == 0
					|| x == (int)ft_strlen(game->map->tab[y]) - 1)
					message_error("Player is out of bounds", game);
				if (!is_valid_adjacent(game->map->tab[y][x - 1])
					|| !is_valid_adjacent(game->map->tab[y][x + 1])
					|| !is_valid_adjacent(game->map->tab[y - 1][x])
					|| !is_valid_adjacent(game->map->tab[y + 1][x]))
					message_error("Player is next to to an invalid case", game);
			}
			x++;
		}
		y++;
	}
}
