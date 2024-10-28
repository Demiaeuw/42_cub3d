/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:50:17 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/22 00:56:40 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

// Main pour afficher le parsing
void	display_parsed_info(char *filename, t_game *game)
{
	write(1, "\n\033[32mParsed Information\033[0m\n\n", 30);
	write(1, "Filename: ", 10);
	write(1, filename, ft_strlen(filename));
	write(1, "\n\n", 2);
	display_texture_info(game);
	display_color_info(game);
	display_map_info(game);
	write(1, "\n", 1);
}

// Affichage des path des textures pour les mur qui ont été parsé
void	display_texture_info(t_game *game)
{
	if (game->infos)
	{
		write(1, "\n\033[32mTextures Paths:\033[0m\n\n", 27);
		write(1, "North Texture: ", 15);
		write(1, game->infos->path_north, ft_strlen(game->infos->path_north));
		write(1, "\n", 1);
		write(1, "South Texture: ", 15);
		write(1, game->infos->path_south, ft_strlen(game->infos->path_south));
		write(1, "\n", 1);
		write(1, "West Texture: ", 14);
		write(1, game->infos->path_west, ft_strlen(game->infos->path_west));
		write(1, "\n", 1);
		write(1, "East Texture: ", 14);
		write(1, game->infos->path_east, ft_strlen(game->infos->path_east));
		write(1, "\n\n", 2);
	}
}

// Affichage des couleur pour le sol et le plafond qui ont été parsé
void	display_color_info(t_game *game)
{
	if (game->map)
	{
		write(1, "\n\033[32mColors ceiling and floor:\033[0m\n\n", 37);
		write(1, "Floor Color: ", 13);
		ft_putnbr_fd(game->map->color_floor, 1);
		write(1, "\n", 1);
		write(1, "Ceiling Color: ", 15);
		ft_putnbr_fd(game->map->color_ceiling, 1);
		write(1, "\n", 1);
	}
}

// Affichage de la map qui a été parsé
void	display_map_info(t_game *game)
{
	if (game->map && game->map->tab)
	{
		write(1, "\n\033[32mMap:\033[0m\n\n", 16);
		int i = 0;
		while (game->map->tab[i])
		{
			write(1, game->map->tab[i], ft_strlen(game->map->tab[i]));
			i++;
		}
	}
}
