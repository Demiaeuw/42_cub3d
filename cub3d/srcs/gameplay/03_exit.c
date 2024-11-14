/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:20:08 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/14 19:59:17 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	cleanup_and_exit(t_game *game)
{
	if (game->infos)
	{
		free(game->infos->path_north);
		free(game->infos->path_south);
		free(game->infos->path_east);
		free(game->infos->path_west);
		free(game->infos);
	}
	if (game->map)
	{
		free_map_tab(game->map);
		free(game->map);
	}
	if (game->player)
		free(game->player);

	// Libération de la fenêtre avec MinilibX
	// if (game->mlx_ptr && game->win_ptr)
	// {
	//     mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	// }
	free(game);
	exit(0);
}