/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:20:08 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/17 12:44:55 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * - Libère toutes les ressources associées à la structure `t_game`.
 * - Libère les chemins des textures et la structure `infos`.
 * - Libère le tableau de la carte et la structure `map`.
 * - Libère la structure `player`.
 * - Détruit la fenêtre et le contexte MinilibX si initialisés.
 * - Ne gère pas la sortie du programme (gérée par une autre fonction).
 */
void	cleanup_resources(t_game *game)
{
	int i;

	// Libérer les images de image_struct
	if (game->image_struct)
	{
		for (i = 0; i < 4; i++)
		{
			if (game->image_struct[i])
			{
				mlx_destroy_image(game->mlx, game->image_struct[i]);
				game->image_struct[i] = NULL;
			}
		}
		free(game->image_struct);
		game->image_struct = NULL;
	}

	if (game->infos)
	{
		free(game->infos->path_north);
		free(game->infos->path_south);
		free(game->infos->path_east);
		free(game->infos->path_west);
		free(game->infos);
	}
	if (game->map)
	{
		free_map_tab(game->map);
		free(game->map);
	}
	if (game->player)
		free(game->player);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	cleanup_ressources_two(t_game *game)
{
	int i;

	// Libérer les textures
	if (game->texture)
	{
		for (i = 0; i < 4; i++)
		{
			if (game->texture[i])
				game->texture[i] = NULL;
		}
		free(game->texture);
		game->texture = NULL;
	}

	if (game->dda)
		free(game->dda);
	if (game->col_data)
		free(game->col_data);
	if (game->rendcoldata)
		free(game->rendcoldata);
}


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
