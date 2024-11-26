/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_print_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:23:44 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/26 11:53:57 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

#define GREEN "\033[32m"
#define RESET "\033[0m"

/**
 * - Affiche les informations de la structure `t_wallstruct`.
 * - Montre les valeurs des champs : `image`, `pixel`, `bit_pixel`,
 *   `size_line`, et `endian`.
 * - Ajoute un titre coloré "Wallstruct:" en vert.
 */
void	print_wallstruct(t_wallstruct *wall)
{
	printf(GREEN "Wallstruct:\n" RESET);
	if (wall != NULL)
	{
		printf("  Image: %p\n", wall->image);
		printf("  Pixel: %p\n", wall->pixel);
		printf("  Bit per Pixel: %d\n", wall->bit_pixel);
		printf("  Size Line: %d\n", wall->size_line);
		printf("  Endian: %d\n", wall->endian);
	}
	else
	{
		printf("  Wallstruct: (null)\n");
	}
	printf("\n");
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
	if (game->wallstruct != NULL)
		printf("  Wallstruct Address: %p\n", (void *)game->wallstruct);
	else
		printf("  Wallstruct Address: (null)\n");
	printf("\n");
	print_game_infos_two(game);
}

void	print_game_infos_two(t_game *game)
{
	if (game->infos != NULL)
		print_info(game->infos);
	else
		printf(GREEN "Infos:\n" RESET "  Infos: (null)\n");
	if (game->player != NULL)
		print_player(game->player);
	else
		printf(GREEN "Player:\n" RESET "  Player: (null)\n");
	if (game->wallstruct != NULL)
		print_wallstruct(game->wallstruct);
	else
		printf(GREEN "Wallstruct:\n" RESET "  Wallstruct: (null)\n");
	if (game->map != NULL)
		print_map(game->map);
	else
		printf(GREEN "Map:\n" RESET "  Map: (null)\n");
}
