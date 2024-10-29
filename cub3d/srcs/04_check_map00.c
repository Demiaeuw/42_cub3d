/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_check_map00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:13:17 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/29 11:18:16 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

// Fonction de vérification du contenue de la map 
void	check_mapcontent(t_map *map)
{
	int row;
	int col;
	int count_player;

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

	// Appeler la fonction de vérification des murs après avoir validé le contenu de la map
	map_check_wall(map->tab, map->position_start_x, map->position_start_y);
}

void validate_map_cell(char cell, int *count_player, t_map *map, int row, int col)
{
    if (cell != '0' && cell != '1' &&
        cell != 'N' && cell != 'S' &&
        cell != 'E' && cell != 'W' &&
        cell != ' ' && cell != '\t' && cell != '\n' && cell != '\0')
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
