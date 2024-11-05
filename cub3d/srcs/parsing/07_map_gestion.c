/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_map_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:53:35 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/05 17:13:07 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	map_gestion(char *filename, t_game *game)
{
	check_map_characters(filename);
	copy_map(filename, game);
}

int	is_valid_map_character(char c)
{
	return (c == ' ' || c == '\t' || c == '1' || c == '0'
			|| c == 'N' || c == 'S' || c == 'W' || c == 'E'
			|| c == '\n' || c == '\0');
}

void	check_map_characters(char *filename)
{
	int		fd;
	char	*line;
	int		is_map_section;
	int		i;

	is_map_section = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		message_error("Failed to open file");

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!is_map_section && (*line == '1' || *line == '0' || *line == ' ' || *line == '\t'))
			is_map_section = 1;
		if (is_map_section)
		{
			i = 0;
			while (line[i] != '\0')
			{
				if (!is_valid_map_character(line[i]))
				{
					free(line);
					close(fd);
					message_error("Invalid character in map");
				}
				i++;
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	count_map_lines(int fd)
{
	int		line_count = 0;
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		// Compte les lignes après le début de la carte
		if (*line == '1' || *line == '0' || *line == ' ' || *line == '\t')
			line_count++;
		free(line);
		line = get_next_line(fd);
	}
	return (line_count);
}

void	copy_map(char *filename, t_game *game)
{
	int		fd;
	int		i;
	char	*line;
	int		is_map_section;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		message_error("Failed to open file");

	// Compte le nombre de lignes de la carte
	int map_lines = count_map_lines(fd);
	close(fd);

	// Allocation de mémoire pour la carte
	game->map->tab = (char **)malloc((map_lines + 1) * sizeof(char *));
	if (!game->map->tab)
		message_error("Memory allocation failed for map");

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		message_error("Failed to reopen file");

	is_map_section = 0;
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		// Détecte le début de la carte
		if (!is_map_section && (*line == '1' || *line == '0' || *line == ' ' || *line == '\t'))
			is_map_section = 1;

		// Si dans la section de la carte, copie chaque ligne dans `tab`
		if (is_map_section)
		{
			game->map->tab[i] = strdup(line);
			if (!game->map->tab[i])
			{
				free(line);
				close(fd);
				message_error("Memory allocation failed for map line");
			}
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	game->map->tab[i] = NULL; // Marque la fin de la carte
	close(fd);
}