/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_check_map01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:18:52 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/29 16:34:54 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

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

void check_map(t_game *game)
{
    int row = 1;
    int col;
    int width = game->map->width;
    int height = game->map->height;

    // Check the first and last row
    col = 0;
    while (col < width)
    {
        if (game->map->tab[0][col] != '1' && game->map->tab[0][col] != ' ' && game->map->tab[0][col] != '\t')
            main_error("Error: Invalid character in the first row. Only '1', ' ', or '\\t' are allowed.");
        if (game->map->tab[height - 1][col] != '1' && game->map->tab[height - 1][col] != ' ' && game->map->tab[height - 1][col] != '\t')
            main_error("Error: Invalid character in the last row. Only '1', ' ', or '\\t' are allowed.");
        col++;
    }

    // Check the internal rows (excluding the borders)
    while (row < height - 1)
    {
        col = 1;
        while (col < width - 1)
        {
            if (game->map->tab[row][col] == '0')
            {
                // Check neighbors of '0' (up, down, left, right)
                if (!is_valid_neighbor(game->map->tab, row - 1, col, width, height) ||  // Up
                    !is_valid_neighbor(game->map->tab, row + 1, col, width, height) ||  // Down
                    !is_valid_neighbor(game->map->tab, row, col - 1, width, height) ||  // Left
                    !is_valid_neighbor(game->map->tab, row, col + 1, width, height))    // Right
                {
                    main_error("Error: Invalid adjacency near '0'.");
                }
            }
            col++;
        }
        row++;
    }
}

