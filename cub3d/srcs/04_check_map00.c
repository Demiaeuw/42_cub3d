/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_check_map00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:13:17 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/28 15:26:27 by acabarba         ###   ########.fr       */
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
	map_check_wall(map->tab);
}

// Fonction qui vérifie si le contenue de la map est bon
void	validate_map_cell(char cell, int *count_player, t_map *map,
	int row, int col)
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
void	map_check_wall(char **tab)
{
    int i, j;
    int height = 0;
    int width;

    // Calculer la hauteur de la carte
    while (tab[height])
        height++;

    // Vérifier si la carte est vide
    if (height == 0)
        main_error("Map is empty");

    // Calculer la largeur de la carte (on suppose que toutes les lignes ont la même longueur)
    width = ft_strlen(tab[0]);

    // Vérifier les bords supérieurs et inférieurs
    for (j = 0; j < width; j++)
    {
        if (tab[0][j] != '1' && tab[0][j] != ' ')
            main_error("Top border is not enclosed by walls");
        if (tab[height - 1][j] != '1' && tab[height - 1][j] != ' ')
            main_error("Bottom border is not enclosed by walls");
    }

    // Vérifier les bords gauche et droit, ainsi que les cases intérieures
    for (i = 0; i < height; i++)
    {
        if (tab[i][0] != '1' && tab[i][0] != ' ')
            main_error("Left border is not enclosed by walls");
        if (tab[i][width - 1] != '1' && tab[i][width - 1] != ' ')
            main_error("Right border is not enclosed by walls");

        for (j = 0; j < width; j++)
        {
            if (tab[i][j] == '0' || tab[i][j] == 'N' || tab[i][j] == 'S' || tab[i][j] == 'E' || tab[i][j] == 'W')
            {
                // Vérifier si la case est bien entourée de murs
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                    main_error("Map is not enclosed by walls");
                if (tab[i - 1][j] == ' ' || tab[i + 1][j] == ' ' || tab[i][j - 1] == ' ' || tab[i][j + 1] == ' ')
                    main_error("Map has a hole or is not properly enclosed");
                if (tab[i - 1][j] != '1' && tab[i - 1][j] != '0' && tab[i - 1][j] != 'N' && tab[i - 1][j] != 'S' && tab[i - 1][j] != 'E' && tab[i - 1][j] != 'W' &&
                    tab[i + 1][j] != '1' && tab[i + 1][j] != '0' && tab[i + 1][j] != 'N' && tab[i + 1][j] != 'S' && tab[i + 1][j] != 'E' && tab[i + 1][j] != 'W' &&
                    tab[i][j - 1] != '1' && tab[i][j - 1] != '0' && tab[i][j - 1] != 'N' && tab[i][j - 1] != 'S' && tab[i][j - 1] != 'E' && tab[i][j - 1] != 'W' &&
                    tab[i][j + 1] != '1' && tab[i][j + 1] != '0' && tab[i][j + 1] != 'N' && tab[i][j + 1] != 'S' && tab[i][j + 1] != 'E' && tab[i][j + 1] != 'W')
                    main_error("Map is not properly enclosed by walls");
            }
        }
    }
}
