/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_second_calque.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:28:35 by kpourcel          #+#    #+#             */
/*   Updated: 2024/12/15 21:28:47 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	init_step_and_side_dist_x(t_game *game)
{
	if (game->col_data->ray_dir_x < 0)
	{
		game->dda->step_x = -1;
		game->dda->side_dist_x = (game->player->x - game->dda->map_x)
			* game->dda->delta_dist_x;
	}
	else
	{
		game->dda->step_x = 1;
		game->dda->side_dist_x = (game->dda->map_x + 1.0 - game->player->x)
			* game->dda->delta_dist_x;
	}
}

void	init_step_and_side_dist_y(t_game *game)
{
	if (game->col_data->ray_dir_y < 0)
	{
		game->dda->step_y = -1;
		game->dda->side_dist_y = (game->player->y - game->dda->map_y)
			* game->dda->delta_dist_y;
	}
	else
	{
		game->dda->step_y = 1;
		game->dda->side_dist_y = (game->dda->map_y + 1.0 - game->player->y)
			* game->dda->delta_dist_y;
	}
}

void	init_step_and_side_dist(t_game *game)
{
	game->dda->delta_dist_x = fabs(1 / game->col_data->ray_dir_x);
	game->dda->delta_dist_y = fabs(1 / game->col_data->ray_dir_y);
	init_step_and_side_dist_x(game);
	init_step_and_side_dist_y(game);
}
