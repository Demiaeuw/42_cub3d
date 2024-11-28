/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_map_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:43 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/28 14:57:03 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * - Parcourt la carte pour chaque case contenant '0', 'N', 'S', 'E' ou 'W'.
 * - Vérifie que ces cases sont entourées de murs avec `check_adjacent`.
 * - Quitte le programme si une case n'est pas sécurisée.
 */
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
				if (check_adjacent(game->map->tab, x, y, game->map->height))
					message_error("Map is not surrounded by walls", game);
			x++;
		}
		y++;
	}
}

/**
 * - Vérifie si un caractère correspond à un joueur ('N', 'S', 'W', 'E').
 * - Retourne 1 si vrai, 0 sinon.
 */
int	is_player_character(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

/**
 * - Vérifie si un caractère adjacent est valide ('0' ou '1').
 * - Retourne 1 si valide, 0 sinon.
 */
int	is_valid_adjacent(char c)
{
	return (c == '0' || c == '1');
}

/**
 * - Parcourt la carte pour trouver la position du joueur ('N', 'S', 'W', 'E').
 * - Vérifie que le joueur n'est pas en bordure de la carte.
 * - Vérifie que les cases adjacentes au joueur sont valides ('0' ou '1').
 * - Quitte le programme si une vérification échoue.
 */
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
