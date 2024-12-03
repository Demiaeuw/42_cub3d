/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:42:29 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/03 18:08:25 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	draw_square(void *mlx, void *win, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(mlx, win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_game *game)
{
	int		x;
	int		y;
	int		tile_size;
	int		color;

	tile_size = 20;
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map->tab[y]))
		{
			if (game->map->tab[y][x] == '1')
				color = 0x000000; // Noir
			else if (x == (int)game->player->x && y == (int)game->player->y)
				color = 0xFF0000; // Rouge
			else if (game->map->tab[y][x] == '0')
				color = 0xFFFFFF;
			else
				color = 0x000000;
			draw_square(game->mlx, game->win_minimap, x * tile_size,
						y * tile_size, tile_size, color);
			x++;
		}
		y++;
	}
}
