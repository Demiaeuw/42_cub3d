/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_render_colomn_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:16:32 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/16 18:56:15 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	calculate_column_height(t_game *game)
{
	t_render_colomn_data	*data;

	data = game->rendcoldata;
	data->line_height = (int)(game->screen_height / game->col_data->perp_dist);
	data->draw_start = -data->line_height / 2 + game->screen_height / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + game->screen_height / 2;
	if (data->draw_end >= game->screen_height)
		data->draw_end = game->screen_height - 1;
}

void	determine_texture_id(t_game *game)
{
	t_render_colomn_data	*data;

	data = game->rendcoldata;
	if (game->dda->hit_direction == 'N')
		data->texture_id = 0;
	else if (game->dda->hit_direction == 'S')
		data->texture_id = 1;
	else if (game->dda->hit_direction == 'E')
		data->texture_id = 2;
	else
		data->texture_id = 3;
}

void	calculate_wall_hit(t_game *game)
{
	t_render_colomn_data	*data;

	data = game->rendcoldata;
	if (game->dda->side == 0)
		data->wall_hit = game->player->y + game->col_data->perp_dist \
			* game->col_data->ray_dir_y;
	else
		data->wall_hit = game->player->x + game->col_data->perp_dist \
			* game->col_data->ray_dir_x;
	data->wall_hit -= floor(data->wall_hit);
}

void	calculate_texture_coordinates(t_game *game)
{
	t_render_colomn_data	*data;

	data = game->rendcoldata;
	data->tex_x = (int)(data->wall_hit * 64);
	if ((game->dda->side == 0 && game->col_data->ray_dir_x > 0)
		|| (game->dda->side == 1 && game->col_data->ray_dir_y < 0))
		data->tex_x = 64 - data->tex_x - 1;
	data->step = 64.0 / data->line_height;
	data->tex_pos = (data->draw_start - game->screen_height \
		/ 2 + data->line_height / 2) * data->step;
}

void	draw_column(t_game *game, int column)
{
	t_render_colomn_data	*data;

	data = game->rendcoldata;
	data->y = data->draw_start;
	while (data->y <= data->draw_end)
	{
		data->tex_y = (int)data->tex_pos & 63;
		data->tex_pos += data->step;
		data->color = game->texture[data->texture_id][data->tex_y \
			* 64 + data->tex_x];
		*((unsigned int *)(game->addr + (data->y * game->line_length \
			+ column * (game->bpp / 8)))) = data->color;
		data->y++;
	}
}
