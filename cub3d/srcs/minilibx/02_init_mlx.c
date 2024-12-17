/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:32:01 by kpourcel          #+#    #+#             */
/*   Updated: 2024/12/17 15:32:18 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

#include <stdlib.h>

void	free_loaded_textures(void *mlx, void **textures, int count)
{
	int	i;

	i = 0;
	if (!textures)
		return ;
	while (i < count)
	{
		if (textures[i])
		{
			mlx_destroy_image(mlx, textures[i]);
			textures[i] = NULL;
		}
		i++;
	}
	free(textures);
	textures = NULL;
}

void	exit_cleanup(t_game *game)
{
	if (game->texture)
		free_loaded_textures(game->mlx, (void **)game->texture, 0);
	cleanup_resources(game);
	free(game);
}

int	exit_on_texture_failure(t_game *game, int loaded_count)
{
	if (game)
	{
		if (game->texture)
			free_loaded_textures(game->mlx,
				(void **)game->texture, loaded_count);
		cleanup_resources(game);
		free(game);
	}
	exit(EXIT_FAILURE);
	return (-1);
}
