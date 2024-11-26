/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_print_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:35:12 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/26 11:24:07 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

#define GREEN "\033[32m"
#define RESET "\033[0m"

/**
 * - Affiche les chemins des textures (North, South, East, West).
 * - Indique "(null)" si un chemin n'est pas défini.
 * - Ajoute un titre coloré "Infos:" en vert.
 */
void	print_info(t_info *infos)
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

/**
 * - Affiche chaque ligne du tableau de la carte.
 * - Parcourt le tableau jusqu'à rencontrer une valeur NULL.
 * - Indente chaque ligne affichée pour améliorer la lisibilité.
 */
void	print_map_layout(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		printf("	%s", tab[i]);
		i++;
	}
}

/**
 * - Affiche les informations du joueur.
 * - Montre les coordonnées X et Y de la position du joueur.
 * - Affiche les composantes X et Y de la direction du joueur.
 * - Ajoute un titre coloré "Player:" en vert.
 */
void	print_player(t_player *player)
{
	printf(GREEN "Player:\n" RESET);
	printf("  Position X: %.2f\n", player->x);
	printf("  Position Y: %.2f\n", player->y);
	printf("  Direction X: %.2f\n", player->direction_x);
	printf("  Direction Y: %.2f\n", player->direction_y);
	printf("\n");
}

/**
 * - Affiche les informations générales de la carte :
 *   - Hauteur.
 *   - Couleurs du sol et du plafond.
 *   - Nombre de joueurs détectés.
 *   - Direction de départ.
 *   - Position de départ (X, Y).
 * - Affiche le contenu du tableau de la carte si disponible.
 * - Ajoute un titre coloré "Map:" en vert.
 */
void	print_map(t_map *map)
{
	printf(GREEN "Map:\n" RESET);
	printf("  Height: %d\n", map->height);
	printf("  Color Floor: %d\n", map->color_floor);
	printf("  Color Ceiling: %d\n", map->color_ceiling);
	printf("  Player count : %d\n", map->player_count);
	if (map->direction_start != '\0')
		printf("  Direction Start: %c\n", map->direction_start);
	else
		printf("  Direction Start: -\n");
	printf("  Position Start X: %d\n", map->position_start_x);
	printf("  Position Start Y: %d\n", map->position_start_y);
	if (map->tab != NULL)
	{
		printf("  Map Layout:\n");
		print_map_layout(map->tab);
	}
	else
	{
		printf("  Map Layout: (null)\n");
	}
	printf("\n\n");
}
