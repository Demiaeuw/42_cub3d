/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parsing_file02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:33:21 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/17 15:57:03 by acabarba         ###   ########.fr       */
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
void	get_map(t_map *map, char *filename)
{
	int		fd;
	char	*line;
	int		map_started;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		main_error("Failed to open file");
	map->heinght = get_map_size(filename);
	map->width = get_map_width(filename);
	map->tab = (char **)malloc(sizeof(char *) * (map->heinght + 1));
	if (!map->tab)
		main_error("Memory allocation failed");
	map_started = 0;
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] == '1' || line[0] == '0')
		{
			map_started = 1;
			map->tab[i++] = line;
		}
		else if (map_started)
		{
			free(line);
			break;
		}
		else
			free(line);
	}
	map->tab[i] = NULL;
	close(fd);
}
