/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_gameplay.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:02:25 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/28 15:54:33 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	gameplay(t_event_list *game)
{
	(void)game;
}

/**
 * Fonction qui permet de modifier la valeur de 0 / 1 lors
 * de l'appuie d'une touche
 */
 void	handle_key_press(int keycode, t_game *game)
 {
	if (keycode == KEY_W)
		game->player->w = 1;
	else if (keycode == KEY_A)
		game->player->a = 1;
	else if (keycode == KEY_S)
		game->player->s = 1;
	else if (keycode == KEY_D)
		game->player->d = 1;
	else if (keycode == KEY_UP)
		game->player->up = 1;
	else if (keycode == KEY_LEFT)
		game->player->left = 1;
	else if (keycode == KEY_DOWN)
		game->player->down = 1;
	else if (keycode == KEY_RIGHT)
		game->player->right = 1;
 }

/**
 * Fonction qui permet de modifier la valeur de 0 / 1 lors
 * du relachement d'une touche
*/
 void	handle_key_release(int keycode, t_game *game)
 {
	if (keycode == KEY_W)
		game->player->w = 0;
	else if (keycode == KEY_A)
		game->player->a = 0;
	else if (keycode == KEY_S)
		game->player->s = 0;
	else if (keycode == KEY_D)
		game->player->d = 0;
	else if (keycode == KEY_UP)
		game->player->up = 0;
	else if (keycode == KEY_LEFT)
		game->player->left = 0;
	else if (keycode == KEY_DOWN)
		game->player->down = 0;
	else if (keycode == KEY_RIGHT)
		game->player->right = 0;
 }
