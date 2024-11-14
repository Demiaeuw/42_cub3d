/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_map_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:02 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/14 19:44:27 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

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

void	check_adjacent(char **tab, int x, int y, int height)
{
	int		width;

	width = ft_strlen(tab[y]);
	if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
		message_error("Map is not surrounded by walls", NULL);
	if (tab[y][x - 1] == ' ' || tab[y][x + 1] == ' '
		|| tab[y - 1][x] == ' ' || tab[y + 1][x] == ' '
		|| tab[y][x - 1] == '\t' || tab[y][x + 1] == '\t'
		|| tab[y - 1][x] == '\t' || tab[y + 1][x] == '\t'
		|| tab[y][x - 1] == '\0' || tab[y][x + 1] == '\0'
		|| tab[y - 1][x] == '\0' || tab[y + 1][x] == '\0')
		message_error("Map is not surrounded by walls", NULL);
}
