/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:15:39 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/05 14:22:24 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	main_parsing(int ac, char **av, t_game **game)
{
	//check nombre d'argument													ok
	check_argument(ac);
	//check .cub																ok
	//check fichier existe														ok
	//check fichier vide														ok
	check_file(av[1]);
	//check que la map est bien le dernier element du fichier					ok
	check_struct_file(av[1]);
	//init des structures														ok
	init_game(game);
	//check presence des 4 path avec les bonnes extension + ajout				ok
	path_gestion(av[1], game);
	//check presence des couleur au bon format + ajout							ok
	color_gestion(av[1], game);
	//check map correct + ajout
	//check si que rien apres la map
	map_gestion(av[1], game);
}
