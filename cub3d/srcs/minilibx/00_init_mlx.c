/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 04:31:01 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/21 05:27:17 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * - Initialise le contexte MinilibX avec `mlx_init`.
 * - Crée une fenêtre principale de 800x600 avec un titre personnalisé.
 * - Retourne -1 et affiche un message d'erreur si l'initialisation
 * ou la création de la fenêtre échoue, en libérant les ressources allouées.
 * - Retourne 0 si l'initialisation réussit.
 */
int	init_mlx_and_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error\nMinilibX initialization failed\n", 2);
		return (-1);
	}
	game->win = mlx_new_window(game->mlx, 800, 600, "Cub3D by Demia & Middle");
	if (!game->win)
	{
		ft_putstr_fd("Error\nWindow creation failed\n", 2);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (-1);
	}
	return (0);
}
