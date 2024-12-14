/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:29:01 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/14 17:36:30 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

int	main(int ac, char **av)
{
	t_game	*game;

	main_parsing(ac, av, &game);
	init_dela_mlx(game);

	// Vérification des fenêtres
	if (!game->win)
	{
		fprintf(stderr, "Error: Failed to create windows.\n");
		cleanup_and_exit(game);
		return (EXIT_FAILURE);
	}

	// Debugging - affichage des infos de jeu (à supprimer plus tard)
	print_game_info(game);

	// Ajout des hooks pour les événements
	mlx_hook(game->win, 2, 1L << 0, handle_key_press, game); 			// KEY_PRESS
	mlx_hook(game->win, 3, 1L << 1, handle_key_release, game); 			// KEY_RELEASE
	mlx_hook(game->win, 17, 0, handle_close, game); 					// Événement de fermeture

	// Boucle principale de rendu
	mlx_loop_hook(game->mlx, render, game);

	// Lancement de la boucle MinilibX
	mlx_loop(game->mlx);

	// Libération des ressources en cas de sortie
	cleanup_and_exit(game);
	return (EXIT_SUCCESS);
}

