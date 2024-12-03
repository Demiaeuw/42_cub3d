/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_init_game2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:47:32 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/03 17:43:33 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * Initialise la structure `t_game` qui contient toutes les données du jeu,
 * incluant les informations de texture (`t_info`), la carte (`t_map`),
 * et le joueur (`t_player`). Vérifie que chaque sous-structure est correctement
 * allouée et initialise également MinilibX et la fenêtre. En cas d'erreur
 * d'initialisation ou d'allocation, libère les ressources et retourne NULL.
 */
t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->infos = init_info();
	game->map = init_map();
	game->player = init_player();
	game->dda = init_dda();
	game->col_data = init_col_data();
	game->texture = NULL;
	game->screen_width = 800;
	game->screen_height = 600;
	game->win = NULL;
	game->win_minimap = NULL;
	game->mlx = NULL;
	if (!game->infos || !game->map || !game->player)
	{
		cleanup_and_exit(game);
		return (NULL);
	}
	return (game);
}
