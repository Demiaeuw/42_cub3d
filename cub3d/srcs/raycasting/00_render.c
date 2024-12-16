/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 02:30:34 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/16 17:22:24 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	render(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	process_mouvement(game);
	handle_camera_rotation(game);
	draw_floor_and_ceiling(game);
	render_walls(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
