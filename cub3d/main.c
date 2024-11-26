/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:29:01 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/26 13:49:34 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

int	main(int ac, char **av)
{
	t_game	*game;

	main_parsing(ac, av, &game);
	init_dela_mlx(game);
	print_game_info(game);
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_hook(game->win, 17, 0, handle_close, game);
	mlx_loop(game->mlx);
	cleanup_and_exit(game);
	return (EXIT_SUCCESS);
}
