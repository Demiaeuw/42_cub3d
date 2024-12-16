/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 02:30:34 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/16 14:46:11 by kpourcel         ###   ########.fr       */
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
	//printf("  Position X: %.2f\n", game->player->x);	// a delete pour test
	//printf("  Position Y: %.2f\n", game->player->y);	// a delete pour test
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
