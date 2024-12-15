/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_gameplay.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:02:25 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/15 20:40:53 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * Fonction qui permet de modifier la valeur de 0 / 1 lors
 * de l'appuie d'une touche
 */
int	handle_key_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
	{
		printf("Escape pressed. Exiting...\n");
		cleanup_and_exit(game);
		exit(EXIT_SUCCESS);
	}
	handle_movement_keys(keycode, game);
	return (0);
}

void	handle_movement_keys(int keycode, t_game *game)
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
int	handle_key_release(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
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
	return (0);
}
