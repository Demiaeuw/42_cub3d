/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_path_gestion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:42:40 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/26 13:23:15 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * Vérifie si le chemin de fichier donné possède l'extension `.xpm`.
 * Retourne 1 si l'extension est valide, 0 sinon.
 */
int	check_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strcmp(path + len - 4, ".xpm") != 0)
		return (0);
	return (1);
}

/**
 * Définit le chemin d'une texture en dupliquant la chaîne `path` 
 * et en la stockant dans `destination`. Libère la mémoire précédente
 * si `destination` contient déjà une valeur. En cas d'échec d'allocation,
 * affiche un message d'erreur et quitte le programme.
 */
void	set_texture_path(char **destination, char *path, t_game *game)
{
	if (*destination != NULL)
	{
		free(*destination);
	}
	*destination = ft_strdup(path);
	if (*destination == NULL)
	{
		message_error("Failed to allocate memory for texture path", game);
	}
}

/**
 * Supprime le caractère de nouvelle ligne (`\n`) à la fin de la chaîne `line`,
 * si celui-ci est présent.
 */
void	remove_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

/**
 * Gère les chemins des textures en lisant le fichier de configuration.
 * Identifie les lignes correspondant aux textures (NO, SO, EA, WE) et 
 * vérifie si leurs chemins possèdent une extension valide `.xpm`.
 * Définit les chemins dans la structure `t_game` à l'aide de `set_texture_path`.
 * Affiche une erreur et quitte si un chemin de
 * texture est manquant ou si le fichier est inaccessible.
 */
void	path_gestion(char *filename, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		message_error("Failed to open file", game);
	line = get_next_line(fd);
	while (line)
	{
		remove_newline(line);
		printf("Debug: Reading line: '%s'\n", line); // Ajout de débogage

		if (ft_strncmp(line, "NO ", 3) == 0 && check_extension(line + 3))
		{
			set_texture_path(&game->infos->path_north, line + 3, game);
			printf("Debug: Set path_north: %s\n", game->infos->path_north);
		}
		else if (ft_strncmp(line, "SO ", 3) == 0 && check_extension(line + 3))
		{
			set_texture_path(&game->infos->path_south, line + 3, game);
			printf("Debug: Set path_south: %s\n", game->infos->path_south);
		}
		else if (ft_strncmp(line, "EA ", 3) == 0 && check_extension(line + 3))
		{
			set_texture_path(&game->infos->path_east, line + 3, game);
			printf("Debug: Set path_east: %s\n", game->infos->path_east);
		}
		else if (ft_strncmp(line, "WE ", 3) == 0 && check_extension(line + 3))
		{
			set_texture_path(&game->infos->path_west, line + 3, game);
			printf("Debug: Set path_west: %s\n", game->infos->path_west);
		}
		else
		{
			printf("Debug: Skipping line: '%s'\n", line); // Si aucune condition n'est remplie
		}

		free(line);
		line = get_next_line(fd);
	}
	close(fd);

	// Vérification finale
	if (!game->infos->path_north || !game->infos->path_south
		|| !game->infos->path_east || !game->infos->path_west)
		message_error("Missing one or more texture paths", game);
}
