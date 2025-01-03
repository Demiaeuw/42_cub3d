/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:21:46 by kpourcel          #+#    #+#             */
/*   Updated: 2025/01/03 17:39:58 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void free_texture(t_game *game)
{
    int i;

    if (!game || !game->texture)
        return;

    i = 0;
    while (i < 4)
    {
        if (game->texture[i])
        {
            free(game->texture[i]);
            game->texture[i] = NULL;
        }
        i++;
    }
    free(game->texture);
    game->texture = NULL;
}


void	free_other_resources(t_game *game)
{
	if (game->dda)
	{
		free(game->dda);
		game->dda = NULL;
	}
	if (game->col_data)
	{
		free(game->col_data);
		game->col_data = NULL;
	}
	if (game->rendcoldata)
	{
		free(game->rendcoldata);
		game->rendcoldata = NULL;
	}
}

void	cleanup_ressources_two(t_game *game)
{
	if (!game)
		return ;
	free_texture(game);
	free_other_resources(game);
}
