/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parsing_file01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:25:03 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/20 23:52:03 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void parsing_file(char *filename, t_game *game)
{
	get_texture_paths(game->infos, filename); 									// Récupération des chemins des textures
	get_colors(game->map, filename); 											// Récupération des couleurs du sol et du plafond
	get_map(game->map, filename); 												// Récupération de la carte
}

// Fonction qui recupère les paths pour les textures
void	get_texture_paths(t_info *infos, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		main_error("Failed to open file");
	while ((line = get_next_line(fd)) != NULL)
	{
		if (ft_strncmp(line, "NO ", 3) == 0)
			infos->path_north = ft_dup(line + 3);
		else if (ft_strncmp(line, "SO ", 3) == 0)
			infos->path_south = ft_dup(line + 3);
		else if (ft_strncmp(line, "WE ", 3) == 0)
			infos->path_west = ft_dup(line + 3);
		else if (ft_strncmp(line, "EA ", 3) == 0)
			infos->path_east = ft_dup(line + 3);
		free(line);
	}
	close(fd);
}

// Fonction pour récupérer la couleur du sol
long	get_floor_color(char *line)
{
	char	**colors;
	long	color;

	colors = ft_split(line + 2, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2])
		main_error("Invalid floor color format");
	color = (ft_atoi(colors[0]) << 16) | (ft_atoi(colors[1]) << 8) | ft_atoi(colors[2]);
	free(colors[0]);
	free(colors[1]);
	free(colors[2]);
	free(colors);
	return (color);
}

// Fonction pour récupérer la couleur du plafond
long	get_ceiling_color(char *line)
{
	char	**colors;
	int	color;

	colors = ft_split(line + 2, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2])
		main_error("Invalid ceiling color format");
	color = (ft_atoi(colors[0]) << 16) | (ft_atoi(colors[1]) << 8) | ft_atoi(colors[2]);
	free(colors[0]);
	free(colors[1]);
	free(colors[2]);
	free(colors);
	return (color);
}

// Fonction pour recuperer les couleurs du ciel et du sol 

void	get_colors(t_map *map, char *filename)
{
	long	fd;
	char		*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		main_error("Failed to open file");
	while ((line = get_next_line(fd)) != NULL)
	{
		if (ft_strncmp(line, "F ", 2) == 0)
		{
			long color_floor = get_floor_color(line);
			map->color_floor = color_floor;
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			long color_ceiling = get_ceiling_color(line);
			map->color_ceiling = color_ceiling;
		}
		free(line);
	}
	close(fd);
}
