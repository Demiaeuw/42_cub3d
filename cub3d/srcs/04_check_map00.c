/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_check_map00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:13:17 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/22 00:55:21 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

// Fonction de vérification du contenue de la map 
void	check_mapcontent(t_map *map)
{
	int		row;
	int		col;
	int		count_player;

	row = 0;
	count_player = 0;
	while (map->tab[row])
	{
		col = 0;
		while (map->tab[row][col])
		{
			validate_map_cell(map->tab[row][col], &count_player, map, row, col);
			col++;
		}
		row++;
	}
	if (count_player != 1)
		main_error("The map must contain exactly one player.");
}

// Fonction qui vérifie si le contenue de la map est bon
void	validate_map_cell(char cell, int *count_player, t_map *map, int row, int col)
{
	if (cell != '0' && cell != '1' &&
		cell != 'N' && cell != 'S' &&
		cell != 'E' && cell != 'W' &&
		cell != ' ' && cell != '	' && cell != '\n' && cell != '\0')
		main_error("Invalid character in map. Only '0', '1', 'N', 'S', 'E', 'W', spaces, and tabs are allowed.");
	if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
	{
		(*count_player)++;
		record_player_position(map, row, col, cell);
	}
}

// Fonction qui enregistre la position et la direction du player au start
void	record_player_position(t_map *map, int row, int col, char player)
{
	map->direction_start = player;
	map->position_start_x = col;
	map->position_start_y = row;
}

// Fonction qui vérifie si il y a des troue dans la map 
void	check_map_boundaries(t_map *map)
{
	int		row;
	int		col;

	row = 0;
	while (map->tab[row])
	{
		col = 0;
		while (map->tab[row][col])
		{
			if (map->tab[row][col] == ' ' || map->tab[row][col] == '	' || map->tab[row][col] == '\n')
			{
				if ((row > 0 && (map->tab[row - 1][col] != '1'
					&& map->tab[row - 1][col] != ' ' && map->tab[row - 1][col] != '	'))
					|| (map->tab[row + 1] && (map->tab[row + 1][col] != '1'
					&& map->tab[row + 1][col] != ' ' && map->tab[row + 1][col] != '	'))
					|| (col > 0 && (map->tab[row][col - 1] != '1'
					&& map->tab[row][col - 1] != ' ' && map->tab[row][col - 1] != '	'))
					|| (map->tab[row][col + 1] != ' '))
					{
					main_error("Map contains holes. Spaces or tabs must be surrounded by '1' or other spaces/tabs.");
				}
			}
			col++;
		}
		row++;
	}
}