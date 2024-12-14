/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 02:30:34 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/14 18:12:25 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	render(void *param)
{
	t_game	*game;

	game = (t_game *)param;

	// Dessiner le premier calque (sol et plafond)
	draw_floor_and_ceiling(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

	// Dessiner les murs par-dessus
	render_walls(game);

	return (0);
}
