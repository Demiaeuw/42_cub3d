/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_map_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:53:35 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/21 05:17:50 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * Gère la validation et la copie de la carte depuis fichier de configuration.
 * Vérifie les caractères autorisés, s'assure que la carte est entourée de murs,
 * et initialise la position du joueur. En cas de problème, affiche un message
 * d'erreur et quitte le programme.
 */
void	map_gestion(char *filename, t_game *game)
{
	check_map_characters(filename, game);
	copy_map(filename, game);
	check_map_surrounded_by_walls(game);
	check_player_position(game);
	validate_and_save_player_position(game);
}

/**
 * Vérifie si un caractère donné est valide dans la carte.
 * Les caractères autorisés incluent les espaces, tabulations, '1', '0',
 * 'N', 'S', 'W', 'E', ainsi que les sauts de ligne et les caractères
 * de fin de chaîne.
 * Retourne 1 si le caractère est valide, 0 sinon.
 */
int	is_valid_map_character(char c)
{
	return (c == ' ' || c == '\t' || c == '1' || c == '0'
		|| c == 'N' || c == 'S' || c == 'W' || c == 'E'
		|| c == '\n' || c == '\0');
}

/**
 * Valide une ligne de la carte en s'assurant que chaque caractère est autorisé.
 * Si un caractère invalide est détecté, libère la ligne, affiche un message 
 * d'erreur et quitte le programme.
 */
void	validate_map_line(char *line, t_game *game)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!is_valid_map_character(line[i]))
		{
			free(line);
			message_error("Invalid character in map", game);
		}
		i++;
	}
}

/**
 * Vérifie que tous les caractères de la section de la carte dans le fichier
 * de configuration sont valides. Ignore les lignes avant la section de la carte
 * puis valide chaque ligne de la carte avec `validate_map_line`.
 * Affiche un message d'erreur et quitte le programme si un caractère invalide
 * est détecté ou si le fichier ne peut pas être ouvert.
 */
void	check_map_characters(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	int		is_map_section;

	is_map_section = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		message_error("Failed to open file", game);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!is_map_section && (*line == '1' || *line == '0'
				|| *line == ' ' || *line == '\t'))
			is_map_section = 1;
		if (is_map_section)
			validate_map_line(line, game);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

/**
 * Compte le nombre de lignes dans la section de la carte d'un fichier.
 * Une ligne est considérée comme faisant partie de la carte si elle commence
 * par '1', '0', un espace ou une tabulation. Retourne le nombre total de
 * lignes correspondant. 
 */
int	count_map_lines(int fd)
{
	int		line_count;
	char	*line;

	line_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*line == '1' || *line == '0' || *line == ' ' || *line == '\t')
			line_count++;
		free(line);
		line = get_next_line(fd);
	}
	return (line_count);
}
