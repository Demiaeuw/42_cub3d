/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:21:46 by kpourcel          #+#    #+#             */
/*   Updated: 2024/12/17 15:22:13 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	free_texture(t_game *game)
{
	int	i;

	i = 0;
	if (!game->texture)
		return ;
	while (i < 4)
	{
		if (game->texture[i])
			game->texture[i] = NULL;
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
