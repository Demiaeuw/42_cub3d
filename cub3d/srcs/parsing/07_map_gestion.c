/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_map_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:53:35 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/07 14:05:27 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	map_gestion(char *filename, t_game *game)
{
	check_map_characters(filename);
	copy_map(filename, game);
	check_map_surrounded_by_walls(game);
	check_player_position(game->map);
	validate_and_save_player_position(game->map);
}

int	is_valid_map_character(char c)
{
	return (c == ' ' || c == '\t' || c == '1' || c == '0'
		|| c == 'N' || c == 'S' || c == 'W' || c == 'E'
		|| c == '\n' || c == '\0');
}

void	validate_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!is_valid_map_character(line[i]))
		{
			free(line);
			message_error("Invalid character in map");
		}
		i++;
	}
}

void	check_map_characters(char *filename)
{
	int		fd;
	char	*line;
	int		is_map_section;

	is_map_section = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		message_error("Failed to open file");
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!is_map_section && (*line == '1' || *line == '0'
				|| *line == ' ' || *line == '\t'))
			is_map_section = 1;
		if (is_map_section)
			validate_map_line(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

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