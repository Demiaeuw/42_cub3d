/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:29:01 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/16 17:20:37 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

int	main(int ac, char **av)
{
	t_game	*game;

	main_parsing(ac, av, &game);
	init_dela_mlx(game);
	if (!game->win)
	{
		fprintf(stderr, "Error: Failed to create windows.\n");
		cleanup_and_exit(game);
		return (EXIT_FAILURE);
	}
	mlx_hook(game->win, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->win, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->win, 17, 0, handle_close, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
	cleanup_and_exit(game);
	return (EXIT_SUCCESS);
}
