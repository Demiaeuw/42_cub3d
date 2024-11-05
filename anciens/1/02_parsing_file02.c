/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parsing_file02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:33:21 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/29 16:01:24 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

// Fonction pour calculer la largeur de la carte
int	get_map_width(char *filename)
{
	int		fd;
	char	*line;
	int		max_width;
	int		current_width;

	max_width = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		main_error("Failed to open file");
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] == '1' || line[0] == '0')
		{
			current_width = ft_strlen(line);
			if (current_width > max_width)
				max_width = current_width;
		}
		free(line);
	}
	close(fd);
	return max_width;
}

// Fonction pour récupérer la carte et la stocker dans t_map
void	open_file(t_map *map, char *filename, int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
		main_error("Failed to open file");
	map->height = get_map_size(filename);
	map->tab = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!map->tab)
		main_error("Memory allocation failed for map->tab");
}

void	process_map_line(t_map *map, char *line, int *map_started, int *i)
{
	if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
	{
		*map_started = 1;
		map->tab[(*i)++] = ft_dup(line);
	}
	else if (*map_started)
	{
		free(line);
		return;
	}
	else
		free(line);
}

void	get_map(t_map *map, char *filename)
{
	int		fd;
	char	*line;
	int		map_started;
	int		i;

	open_file(map, filename, &fd);
	map_started = 0;
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
		process_map_line(map, line, &map_started, &i);
	map->tab[i] = NULL;
	close(fd);
}
