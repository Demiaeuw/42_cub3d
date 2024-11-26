/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:51:13 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/26 13:30:06 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * Effectue le parsing principal du fichier de configuration `.cub`.
 * Vérifie la validité des arguments et du fichier,
 * initialise les structures du jeu,
 * et remplit les données nécessaires, notamment les textures, les couleurs,
 * la carte, et les informations du joueur.
 */

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
	*game = init_game();
	if (!*game)
		message_error("Failed to initialize game structures", *game);
	//check presence des 4 path avec les bonnes extension + ajout				ok
	path_gestion(av[1], *game);
	//check presence des couleur au bon format + ajout							ok
	color_gestion(av[1], *game);
	//check map correct + ajout													ok
	//check que map valide														ok								
	map_gestion(av[1], *game);
	//maj des infos du player (position / direction)							ok
	player_struct_start(*game);
	init_game_texture(*game);
}
