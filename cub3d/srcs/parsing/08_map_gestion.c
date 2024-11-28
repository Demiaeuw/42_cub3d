/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_map_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:02 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/28 14:55:50 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * Initialise l'espace mémoire pour la carte dans la structure `t_map`.
 * Compte le nombre de lignes dans la section de la carte du fichier pour
 * définir sa hauteur, puis alloue un tableau de chaînes de caractères
 * avec une ligne supplémentaire pour marquer la fin. Affiche un message
 * d'erreur et quitte le programme en cas d'échec d'ouverture du fichier
 * ou d'allocation de mémoire.
 */
void	init_map_space(char *filename, t_game *game)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		message_error("Failed to open file", game);
	game->map->height = count_map_lines(fd);
	close(fd);
	game->map->tab = (char **)malloc((game->map->height + 1) * sizeof(char *));
	if (!game->map->tab)
		message_error("Memory allocation failed for map", game);
}

/**
 * Copie une ligne de la carte dans le tableau `tab` de la structure `t_map`.
 * Alloue dynamiquement la mémoire pour la ligne avec `strdup`. Si l'allocation
 * échoue, libère la ligne, ferme le fichier et affiche un message d'erreur
 * avant de quitter le programme.
 */
void	copy_map_line(t_game *game, char *line, int i, int fd)
{
	game->map->tab[i] = strdup(line);
	if (!game->map->tab[i])
	{
		free(line);
		close(fd);
		message_error("Memory allocation failed for map line", game);
	}
}

/**
 * Remplit le tableau `tab` de la structure `t_map` 
 * avec les lignes de la carte
 * extraites du fichier. Identifie le début de la section de 
 * la carte en recherchant
 * des lignes commençant par '1', '0', un espace ou une 
 * tabulation. Chaque ligne de
 * la carte est copiée dans le tableau via `copy_map_line`.
 *  Ajoute un pointeur NULL
 * à la fin du tableau pour marquer sa fin.
 */
void	fill_map_tab(int fd, t_game *game)
{
	char	*line;
	int		is_map_section;
	int		i;

	i = 0;
	is_map_section = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!is_map_section && (*line == '1' || *line == '0'
				|| *line == ' ' || *line == '\t'))
			is_map_section = 1;
		if (is_map_section)
		{
			copy_map_line(game, line, i, fd);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	game->map->tab[i] = NULL;
}

/**
 * Copie les lignes de la carte d'un fichier dans la structure `t_map`.
 * Initialise l'espace mémoire pour la carte avec `init_map_space`, rouvre
 * le fichier pour lire la carte, et remplit le tableau `tab` avec 
 * `fill_map_tab`. Affiche un message d'erreur et quitte le programme en
 * cas d'échec lors de la réouverture du fichier.
 */
void	copy_map(char *filename, t_game *game)
{
	int	fd;

	init_map_space(filename, game);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		message_error("Failed to reopen file", game);
	fill_map_tab(fd, game);
	close(fd);
}

/**
 * Vérifie que la case (x, y) de la carte est correctement entourée de murs.
 * Si la case est sur le bord de la carte ou adjacente à un espace, une
 * tabulation ou un caractère de fin de ligne, affiche un message d'erreur
 * et quitte le programme, indiquant que la carte n'est pas entourée de murs.
 */
int	check_adjacent(char **tab, int x, int y, int height)
{
	int		width;

	width = ft_strlen(tab[y]);
	if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
		return (1);
	if (tab[y][x - 1] == ' ' || tab[y][x + 1] == ' '
		|| tab[y - 1][x] == ' ' || tab[y + 1][x] == ' '
		|| tab[y][x - 1] == '\t' || tab[y][x + 1] == '\t'
		|| tab[y - 1][x] == '\t' || tab[y + 1][x] == '\t'
		|| tab[y][x - 1] == '\0' || tab[y][x + 1] == '\0'
		|| tab[y - 1][x] == '\0' || tab[y + 1][x] == '\0')
		return (1);
	return (0);
}
