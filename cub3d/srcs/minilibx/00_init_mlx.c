/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 04:31:01 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/26 12:19:42 by acabarba         ###   ########.fr       */
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

/**
 * - Initialise les textures du jeu en chargeant les fichiers `.xpm`
 *   correspondants aux chemins fournis dans `game->infos`.
 * - Alloue un tableau de structures `t_wallstruct` pour stocker les textures.
 * - Remplit chaque élément de ce tableau avec les données des fichiers `.xpm`
 *   pour les directions North, South, East et West.
 * - Utilise `xpm_to_image` pour charger chaque texture.
 * - Quitte avec un message d'erreur via `message_error` si une allocation ou un chargement échoue.
 * - Les ressources de `game->texture` doivent être libérées ultérieurement avec
 *   une fonction appropriée (comme `free_game_texture`).
 */
void	init_game_texture(t_game *game)
{
	game->texture = ft_calloc(5, sizeof * (game->texture)); // a free
	if (!game->texture)
		message_error("init texture tab", game);
	xpm_to_image(game, &game->texture[0], game->infos->path_north);
	xpm_to_image(game, &game->texture[1], game->infos->path_south);
	xpm_to_image(game, &game->texture[2], game->infos->path_east);
	xpm_to_image(game, &game->texture[3], game->infos->path_west);
}

/**
 * - Charge un fichier d'image `.xpm` et stocke ses informations dans une
 *   structure `t_wallstruct` passée en paramètre.
 * - Utilise `mlx_xpm_file_to_image` pour charger l'image dans la mémoire
 *   de MinilibX et en obtenir un pointeur.
 * - Récupère les informations des pixels, bits par pixel, taille de ligne,
 *   et endian avec `mlx_get_data_addr`.
 * - Si le chemin est NULL ou si une étape échoue (chargement de l'image,
 *   récupération des données), la fonction affiche un message d'erreur
 *   via `message_error` et quitte le programme.
 * - Ne retourne rien, mais modifie directement la structure `t_wallstruct`.
 */
void	xpm_to_image(t_game *game, t_wallstruct *wall, char *path)
{
	if (!path)
		message_error("Missing texture path", game);
	wall->image = mlx_xpm_file_to_image(game->mlx, path, &wall->size_line, &wall->endian);
	if (!wall->image)
		message_error("Failed to load texture image", game);
	wall->pixel = (int *)mlx_get_data_addr(wall->image, &wall->bit_pixel, &wall->size_line, &wall->endian);
	if (!wall->pixel)
	{
		mlx_destroy_image(game->mlx, wall->image);
		message_error("Failed to retrieve image data", game);
	}
}
