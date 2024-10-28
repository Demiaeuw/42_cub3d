/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:42:58 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/28 09:22:09 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

// Fonction pour afficher un message d'erreur
void	main_error(char *str)
{
	write(2, "\n\033[31mError\033[0m\n\n", 18);
	write(2, str, ft_strlen(str));
	write(2, "\n\n", 2);
	exit(EXIT_FAILURE);
}

// Fonction pour libérer toutes les allocations
void	main_free(t_game *game)
{
	if (game->infos)
	{
		if (game->infos->path_north != NULL)
			free(game->infos->path_north);
		if (game->infos->path_south != NULL)
			free(game->infos->path_south);
		if (game->infos->path_west != NULL)
			free(game->infos->path_west);
		if (game->infos->path_east != NULL)
			free(game->infos->path_east);
		free(game->infos);
		game->infos = NULL;
	}
	if (game->map)
	{
		int i = 0;
		if (game->map->tab)
		{
			while (game->map->tab[i])
			{
				free(game->map->tab[i]);
				i++;
			}
			free(game->map->tab);
			game->map->tab = NULL;
		}
		free(game->map);
		game->map = NULL;
	}
}
