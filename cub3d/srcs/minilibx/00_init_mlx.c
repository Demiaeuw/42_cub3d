/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 04:31:01 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/16 17:01:50 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	init_dela_mlx(t_game *game)
{
	if (init_mlx_and_window(game) == -1)
	{
		cleanup_and_exit(game);
		return ;
	}
	init_image(game);
	init_game_texture(game);
}

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
	game->win = mlx_new_window(game->mlx, game->screen_width,
			game->screen_height, "Cub3D by Demia & Middle");
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
 * - Quitte avec un message d'erreur via `message_error` si une allocation
 * ou un chargement échoue.
 * - Les ressources de `game->texture` doivent être libérées ultérieurement avec
 *   une fonction appropriée (comme `free_game_texture`).
 */
/*
int	init_game_texture(t_game *game)
{
	void	*image;
	int		i;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	game->texture = ft_calloc(5, sizeof(int *));
	if (!game->texture)
	{
		printf("Error: Failed to allocate memory for textures.\n");
		return (-1);
	}
	char	*paths[4] = {game->infos->path_north, game->infos->path_south,
		game->infos->path_east, game->infos->path_west};
	i = 0;
	while (i < 4)
	{
		image = mlx_xpm_file_to_image(game->mlx, paths[i], &width, &height);
		if (!image)
		{
			printf("Error: Failed to load image from path: %s\n", paths[i]);
			return (-1);
		}
		game->texture[i] = (int *)mlx_get_data_addr(image, &bits_per_pixel,
			&size_line, &endian);
		if (!game->texture[i])
		{
			printf("Error: Failed to get data address for image at path: %s\n",
				paths[i]);
			mlx_destroy_image(game->mlx, image);
			return (-1);
		}
		mlx_destroy_image(game->mlx, image);
		i++;
	}
	return (0);
}
*/
// Fonction pour libérer les textures en cas d'échec
void	free_textures(int **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	print_error(char *message)
{
	printf("%s\n", message);
	return (-1);
}

int	store_texture(t_game *game, int index, void *image)
{
	game->texture[index] = (int *)mlx_get_data_addr(image, &game->bpp,
			&game->line_length,
			&game->endian);
	if (!game->texture[index])
	{
		printf("Error: Failed to get data address for texture %d.\n", index);
		return (-1);
	}
	return (0);
}

int	exit_on_texture_failure(t_game *game, int loaded_count)
{
	if (game)
	{
		if (game->texture)
		{
			int	i = 0;
			while (i < loaded_count) // Libère les textures déjà chargées
			{
				if (game->texture[i])
				{
					mlx_destroy_image(game->mlx, game->texture[i]);
					game->texture[i] = NULL;
				}
				i++;
			}
			free(game->texture); // Libère le tableau des textures
			game->texture = NULL;
		}
		cleanup_resources(game); // Libère les autres ressources
		free(game); // Libère la structure principale
	}
	exit(EXIT_FAILURE); // Quitte le programme avec un statut d'échec
	return (-1); // Retourne une valeur d'erreur pour cohérence
}
