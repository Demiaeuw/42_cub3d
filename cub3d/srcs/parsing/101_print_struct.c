/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_print_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:23:44 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/16 15:26:31 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

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
	printf("  Y: %.2f\n", col_data->ray_dir_y);
	printf("  perp_dist: %.2f\n\n", col_data->perp_dist);
}

void	print_game(t_game *game)
{
	printf(GREEN "GAME:\n" RESET);
	printf("  Adresse fenetre: %p\n", (void *)game->win);
	printf("  Hauteur fenetre: %d\n", game->screen_height);
	printf("  Largeur fenetre: %d\n", game->screen_width);
	printf("  Adresse image du premier calque: %p\n", (void *)game->img);
	printf("  bits par pixel: %d\n", game->bpp);
	printf("  Line length: %d\n", game->line_length);
	printf("  Endian: %d\n\n", game->endian);
}
