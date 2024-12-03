/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_parsing_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:49:24 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/03 14:39:00 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * Affiche un message d'erreur en rouge, libère les ressources,
 * et quitte le programme proprement.
 */
void	message_error(char *str, t_game *game)
{
	write(2, "\n\033[31mError\033[0m\n\n", 18);
	write(2, str, ft_strlen(str));
	write(2, "\n\n", 2);
	// error_clean_exit(game);
	cleanup_resources(game);
	cleanup_ressources_two(game);
	free(game);
	exit(EXIT_FAILURE);
}

/**
 * Libère la mémoire allouée pour le tableau de la carte 
 * ainsi que chaque ligne qu'il contient.
 */

void	free_map_tab(t_map *map)
{
	int	i;

	if (map && map->tab)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->tab[i]);
			i++;
		}
		free(map->tab);
	}
}

/**
 * Libère toutes les ressources allouées associées à la structure `t_game`
 * et à ses sous-structures en cas d'erreur.
 */

void	error_clean_exit(t_game *game)
{
	if (!game)
		return ;
	if (game && game->infos)
	{
		free(game->infos->path_north);
		free(game->infos->path_south);
		free(game->infos->path_east);
		free(game->infos->path_west);
		free(game->infos);
	}
	if (game && game->map)
	{
		free_map_tab(game->map);
		free(game->map);
	}
	if (game && game->player)
		free(game->player);
	if (game)
		free(game);
}
