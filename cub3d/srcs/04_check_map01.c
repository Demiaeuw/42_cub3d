/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_check_map01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:18:52 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/29 16:10:47 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int is_valid_neighbor(char **map, int row, int col, int max_width, int max_height)
{
    if (row < 0 || row >= max_height || col < 0 || col >= max_width)
        return 0;

    char cell = map[row][col];
    if (cell == '0' || cell == '1' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
        return 1;
    
    return 0;
}

// Modification de la vérification de la première et dernière ligne pour afficher le caractère problématique
void check_map(t_game *game)
{
	// int row = 1;
	int col;
	int width = game->map->width;
	int height = game->map->height;

	// Vérifie la première et dernière ligne
	col = 0;
	while (col < width)
	{
		if (game->map->tab[0][col] != '1' && game->map->tab[0][col] != ' ' &&
			game->map->tab[0][col] != '\t' && game->map->tab[0][col] != '\n' &&
			game->map->tab[0][col] != '\r')
		{
			char problem_char = game->map->tab[0][col];
			printf("First row: \"%s\"\n", game->map->tab[0]);
			printf("Problematic character: '%c' at position %d in the first row.\n", problem_char, col);
			main_error("Error: Invalid character in the first row. Only '1', ' ', or '\\t' are allowed.");
		}

		if (game->map->tab[height - 1][col] != '1' && game->map->tab[height - 1][col] != ' ' &&
			game->map->tab[height - 1][col] != '\t' && game->map->tab[height - 1][col] != '\n' &&
			game->map->tab[height - 1][col] != '\r' && game->map->tab[height - 1][col] != '\0')
		{
			char problem_char = game->map->tab[height - 1][col];
			printf("Last row: \"%s\"\n", game->map->tab[height - 1]);
			printf("Problematic character: '%c' at position %d in the last row.\n", problem_char, col);
			main_error("Error: Invalid character in the last row. Only '1', ' ', or '\\t' are allowed.");
		}
		col++;
	}

	// Reste de la vérification de la carte...
}
