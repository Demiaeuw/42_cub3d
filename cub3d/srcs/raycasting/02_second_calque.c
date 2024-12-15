/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_second_calque.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:12:43 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/15 21:34:06 by kpourcel         ###   ########.fr       */
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
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;
	int	color;

	line_height = (int)(game->screen_height / game->col_data->perp_dist);
	draw_start = -line_height / 2 + game->screen_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + game->screen_height / 2;
	if (draw_end >= game->screen_height)
		draw_end = game->screen_height - 1;
	if (game->dda->hit_direction == 'N')
		color = 0xADD8E6;
	else if (game->dda->hit_direction == 'S')
		color = 0x00008B;
	else if (game->dda->hit_direction == 'E')
		color = 0x90EE90;
	else if (game->dda->hit_direction == 'W')
		color = 0x006400;
	y = draw_start;
	while (y <= draw_end)
	{
		*((unsigned int *)(game->addr + (y * game->line_length + column * (game->bpp / 8)))) = color;
		y++;
	}
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
