/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 04:31:01 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/17 15:29:00 by kpourcel         ###   ########.fr       */
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
