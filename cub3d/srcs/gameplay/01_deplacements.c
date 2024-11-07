/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_deplacements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:02:52 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/07 17:05:33 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	move_player(t_player *player, float delta_x, float delta_y)
{
	player->x += delta_x;
	player->y += delta_y;
}

void	handle_movement(int keycode, t_game *game)
{
	float	move_speed = 0.1;

	if (keycode == 'W' || keycode == 'Z')
		move_player(game->player, game->player->direction_x * move_speed,
			game->player->direction_y * move_speed);
	else if (keycode == 'S')
		move_player(game->player, -game->player->direction_x * move_speed,
			-game->player->direction_y * move_speed);
	else if (keycode == 'A' || keycode == 'Q')
		move_player(game->player, -game->player->direction_y * move_speed,
			game->player->direction_x * move_speed);
	else if (keycode == 'D')
		move_player(game->player, game->player->direction_y * move_speed,
			-game->player->direction_x * move_speed);
}
