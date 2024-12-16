/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_second_calque.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:12:43 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/16 18:56:52 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	render_walls(t_game *game)
{
	int	column;

	column = 0;
	while (column < game->screen_width)
	{
		init_ray(game, column);
		init_step_and_side_dist(game);
		perform_dda(game);
		calculate_perp_dist(game);
		render_column(game, column);
		column++;
	}
}

void	calculate_perp_dist(t_game *game)
{
	if (game->dda->side == 0)
	{
		game->col_data->perp_dist = (game->dda->map_x - game->player->x \
			+ (1 - game->dda->step_x) / 2) / game->col_data->ray_dir_x;
	}
	else
	{
		game->col_data->perp_dist = (game->dda->map_y - game->player->y \
			+ (1 - game->dda->step_y) / 2) / game->col_data->ray_dir_y;
	}
}

void	render_column(t_game *game, int column)
{
	calculate_column_height(game);
	determine_texture_id(game);
	calculate_wall_hit(game);
	calculate_texture_coordinates(game);
	draw_column(game, column);
}

void	init_ray(t_game *game, int column)
{
	float	camera_x;

	camera_x = 2 * ((float)column / (float)game->screen_width) - 1;
	game->col_data->ray_dir_x = game->player->dir_x \
		+ game->player->cam_x * camera_x;
	game->col_data->ray_dir_y = game->player->dir_y \
		+ game->player->cam_y * camera_x;
	game->dda->map_x = (int)game->player->x;
	game->dda->map_y = (int)game->player->y;
}
