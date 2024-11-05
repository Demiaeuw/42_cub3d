/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_print_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:35:12 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/05 17:14:49 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

#define GREEN "\033[32m"
#define RESET "\033[0m"

void print_info(t_info *infos)
{
	printf(GREEN "Infos:\n" RESET);
	if (infos->path_north != NULL)
		printf("  Path North: %s\n", infos->path_north);
	else
		printf("  Path North: (null)\n");

	if (infos->path_south != NULL)
		printf("  Path South: %s\n", infos->path_south);
	else
		printf("  Path South: (null)\n");

	if (infos->path_east != NULL)
		printf("  Path East: %s\n", infos->path_east);
	else
		printf("  Path East: (null)\n");

	if (infos->path_west != NULL)
		printf("  Path West: %s\n", infos->path_west);
	else
		printf("  Path West: (null)\n");
	printf("\n");
}

void print_map(t_map *map)
{
	printf(GREEN "Map:\n" RESET);
	printf("  Height: %d\n", map->height);
	printf("  Color Floor: %d\n", map->color_floor);
	printf("  Color Ceiling: %d\n", map->color_ceiling);
	if (map->direction_start != '\0')
		printf("  Direction Start: %c\n", map->direction_start);
	else
		printf("  Direction Start: -\n");
	printf("  Position Start X: %d\n", map->position_start_x);
	printf("  Position Start Y: %d\n", map->position_start_y);
	if (map->tab != NULL)
	{
		printf("  Map Layout:\n");
		for (int i = 0; map->tab[i] != NULL; i++)
			printf("	%s", map->tab[i]);
	}
	else
	{
		printf("  Map Layout: (null)\n");
	}
	printf("\n\n");
}

void print_game_info(t_game *game)
{
	printf(GREEN "Game:\n" RESET);
	if (game->infos != NULL)
		printf("  Info Address: %p\n", (void *)game->infos);
	else
		printf("  Info Address: (null)\n");

	if (game->map != NULL)
		printf("  Map Address: %p\n", (void *)game->map);
	else
		printf("  Map Address: (null)\n");
	printf("\n");
	if (game->infos != NULL)
		print_info(game->infos);
	else
		printf(GREEN "Infos:\n" RESET "  Infos: (null)\n");

	if (game->map != NULL)
		print_map(game->map);
	else
		printf(GREEN "Map:\n" RESET "  Map: (null)\n");
}