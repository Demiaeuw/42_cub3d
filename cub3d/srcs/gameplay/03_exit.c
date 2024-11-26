/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:20:08 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/26 11:58:40 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * - Libère les ressources associées à la structure `t_wallstruct`.
 * - Vérifie si la structure ou ses champs sont non NULL avant de libérer.
 * - N'affecte pas la structure principale `t_game`, cette fonction se concentre
 *   uniquement sur `t_wallstruct`.
 */
void	free_wallstruct(t_wallstruct *wall)
{
	if (!wall)
		return;
	if (wall->image)
	{
		// Si vous utilisez MinilibX, ajoutez la fonction pour détruire l'image.
		// Exemple : mlx_destroy_image(mlx_ptr, wall->image);
		// Remplacez `mlx_ptr` par le pointeur correct de votre contexte MLX.
		// mlx_destroy_image(mlx_ptr, wall->image);
		wall->image = NULL;
	}
	free(wall);
}

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
	if (game->wallstruct)
		free_wallstruct(game->wallstruct);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
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
