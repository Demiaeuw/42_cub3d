/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:29:01 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/03 18:10:25 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

int	main(int ac, char **av)
{
	t_game	*game;

	main_parsing(ac, av, &game);
	init_dela_mlx(game);
	print_game_info(game);
	set_dda(game, game->player->dir_x, game->player->dir_y);		// a delete pour affichage de test
	print_dda(game->dda);											// a delete pour affichage de test
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_hook(game->win, 17, 0, handle_close, game);
	mlx_key_hook(game->win_minimap, handle_keypress, game);
	mlx_hook(game->win_minimap, 17, 0, handle_close, game);
	mlx_loop_hook(game->mlx, render, game);
	// ????? il manque un truc sur les keypress ????
	// mlx_hook(window, KEY_PRESS, 0, handle_key_press, &input);
	// mlx_hook(window, KEY_RELEASE, 0, handle_key_release, &input);
	mlx_loop(game->mlx);
	cleanup_and_exit(game);
	return (EXIT_SUCCESS);
}
