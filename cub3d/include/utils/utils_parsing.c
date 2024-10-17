/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:50:17 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/17 16:16:14 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	display_parsed_info(char *filename, t_game *game)
{
	write(1, "\n\033[32mParsed Information\033[0m\n\n", 30);
	write(1, "Filename: ", 10);
	write(1, filename, ft_strlen(filename));
	write(1, "\n\n", 2);
	write(1, "Textures Paths:\n\n", 15);
	if (game->infos)
	{
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
	write(1, "Colors:\n", 8);
	if (game->map)
	{
		char buffer[20];
		int len;
		len = snprintf(buffer, sizeof(buffer), "Floor Color: %d\n", game->map->color_floor);
		write(1, buffer, len);
		len = snprintf(buffer, sizeof(buffer), "Ceiling Color: %d\n", game->map->color_ceiling);
		write(1, buffer, len);
		write(1, "\n", 1);
	}
	write(1, "Map:\n", 5);
	if (game->map && game->map->tab)
	{
		int i = 0;
		write(1, "\n", 1);
		while (game->map->tab[i])
		{
			write(1, game->map->tab[i], ft_strlen(game->map->tab[i]));
			i++;
		}
		write(1, "\n", 1);
	}
	write(1, "\n\n", 2);
}