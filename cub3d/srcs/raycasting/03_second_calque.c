/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_second_calque.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:20:12 by kpourcel          #+#    #+#             */
/*   Updated: 2024/12/15 21:20:25 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	update_dda_side_dist(t_dda *dda)
{
	if (dda->side_dist_x < dda->side_dist_y)
	{
		dda->side_dist_x += dda->delta_dist_x;
		dda->map_x += dda->step_x;
		dda->side = 0;
	}
	else
	{
		dda->side_dist_y += dda->delta_dist_y;
		dda->map_y += dda->step_y;
		dda->side = 1;
	}
}

void	set_hit_direction(t_game *game)
{
	if (game->dda->side == 0)
	{
		if (game->col_data->ray_dir_x > 0)
			game->dda->hit_direction = 'W';
		else
			game->dda->hit_direction = 'E';
	}
	else
	{
		if (game->col_data->ray_dir_y > 0)
			game->dda->hit_direction = 'N';
		else
			game->dda->hit_direction = 'S';
	}
}

void	perform_dda(t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		update_dda_side_dist(game->dda);
		if (game->map->tab[game->dda->map_y][game->dda->map_x] == '1')
		{
			hit = 1;
			set_hit_direction(game);
		}
	}
}
