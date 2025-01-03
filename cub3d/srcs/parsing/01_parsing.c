/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:51:13 by acabarba          #+#    #+#             */
/*   Updated: 2025/01/03 16:35:27 by kpourcel         ###   ########.fr       */
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
	check_argument(ac);
	check_file(av[1]);
	check_struct_file(av[1]);
	*game = init_game();
	if (!*game)
		message_error("Failed to initialize game structures", *game);
	path_gestion(av[1], *game);
	check_texture_paths(*game);
	color_gestion(av[1], *game);
	map_gestion(av[1], *game);
	player_struct_start(*game);
}
