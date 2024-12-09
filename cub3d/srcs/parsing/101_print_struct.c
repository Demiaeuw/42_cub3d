/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_print_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:23:44 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/03 14:49:00 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

#define GREEN "\033[32m"
#define RESET "\033[0m"

void	print_texture_info(t_game *game)
{
	int	i;

	printf(GREEN "Textures:\n" RESET);
	if (game->texture != NULL)
	{
		i = 0;
		while (i < 4)
		{
			if (game->texture[i] != NULL)
				printf("  Texture[%d] Address: %p\n",
					i, (void *)game->texture[i]);
			else
				printf("  Texture[%d] Address: (null)\n", i);
			i++;
		}
	}
	else
	{
		printf("  Texture Array: (null)\n");
	}
	printf("\n");
}

/**
 * - Affiche les valeurs actuelles de la structure DDA.
 * - Montre les coordonnées de la carte, les distances, et la direction.
 * - Ajoute un titre coloré "DDA:" en vert.
 */
void	print_dda(t_dda *dda)
{
	printf(GREEN "DDA:\n" RESET);
	printf("  Map X: %d\n", dda->map_x);
	printf("  Map Y: %d\n", dda->map_y);
	printf("  Step X: %d\n", dda->step_x);
	printf("  Step Y: %d\n", dda->step_y);
	printf("  Side Dist X: %.2f\n", dda->side_dist_x);
	printf("  Side Dist Y: %.2f\n", dda->side_dist_y);
	printf("  Delta Dist X: %.2f\n", dda->delta_dist_x);
	printf("  Delta Dist Y: %.2f\n", dda->delta_dist_y);
	printf("  Side: %d\n\n", dda->side);
}

/**
 * - Affiche les valeurs actuelles de la structure `col_data`.
 * - Montre les informations liées à une colonne spécifique lors du raycasting :
 *   - Numéro de la colonne.
 *   - Composantes X et Y de la direction du rayon.
 * - Ajoute un titre coloré "Column:" en vert pour une meilleure lisibilité.
 */
void	print_col_info(t_col_data *col_data)
{
	printf(GREEN "Column:\n" RESET);
	printf("  Column: %d\n", col_data->column);
	printf("  X: %.2f\n", col_data->ray_dir_x);
	printf("  Y: %.2f\n\n", col_data->ray_dir_y);
}

/**
 * - Affiche les adresses des structures principales (`infos`, `map`, `player`).
 * - Si les structures sont non nulles, affiche leurs contenus en utilisant :
 *   - `print_info` pour les textures.
 *   - `print_player` pour les informations du joueur.
 *   - `print_map` pour les détails de la carte.
 * - Ajoute des titres colorés ("Game:", "Infos:", "Player:", "Map:") pour une
 *   meilleure lisibilité.
 */
void	print_game_info(t_game *game)
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
	if (game->player != NULL)
		printf("  Player Address: %p\n", (void *)game->player);
	else
		printf("  Player Address: (null)\n");
	printf("\n");
	print_game_infos_two(game);
}

void	print_game_infos_two(t_game *game)
{
	if (game->infos != NULL)
		print_info(game->infos);
	else
		printf(GREEN "Infos:\n" RESET "  Infos: (null)\n");
	if (game->dda != NULL)
		print_dda(game->dda);
	else
		printf(GREEN "DDA:\n" RESET "  DDA: (null)\n");
	if (game->col_data != NULL)
		print_col_info(game->col_data);
	else
		printf(GREEN "Column:\n" RESET "  Column: (null)\n");
	if (game->player != NULL)
		print_player(game->player);
	else
		printf(GREEN "Player:\n" RESET "  Player: (null)\n");
	print_texture_info(game);
	if (game->map != NULL)
		print_map(game->map);
	else
		printf(GREEN "Map:\n" RESET "  Map: (null)\n");
}
