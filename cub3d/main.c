/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:29:01 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/17 15:10:40 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

int	main(int argc, char **argv)
{
	t_game game;
	t_info infos;
	t_map map;

	game.infos = &infos;
	game.map = &map;

	main_parsing(argc, argv, &game);

	// Le reste du programme continue ici...
	main_free(&game);
	return (0);
}