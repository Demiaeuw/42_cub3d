/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:20:08 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/17 15:26:27 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * - Vérifie si la structure `game` est NULL, 
 * quitte avec un échec si c'est le cas.
 * - Appelle `cleanup_resources` pour libérer toutes les ressources associées.
 * - Libère la structure principale `game`.
 * - Quitte le programme avec succès.
 */
void	cleanup_and_exit(t_game *game)
{
	if (!game)
		exit(EXIT_FAILURE);
	cleanup_resources(game);
	cleanup_ressources_two(game);
	free(game);
	exit(EXIT_SUCCESS);
}

/**
 * Fonction de gestion pour quitter le programme avec ECHAP
 */
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		cleanup_and_exit(game);
	}
	return (0);
}

/**
 * Fonction de gestion pour quitter le programme avec la croix
 */
int	handle_close(t_game *game)
{
	cleanup_and_exit(game);
	return (0);
}
