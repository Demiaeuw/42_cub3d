/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parsing_file01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:25:03 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/17 15:46:22 by acabarba         ###   ########.fr       */
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
void	get_floor_color(t_map *map, char *line)
{
	char	**colors;

	colors = ft_split(line + 2, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2])
		main_error("Invalid floor color format");
	map->color_floor = (ft_atoi(colors[0]) << 16) | (ft_atoi(colors[1]) << 8) | ft_atoi(colors[2]);
	free(colors[0]);
	free(colors[1]);
	free(colors[2]);
	free(colors);
}

// Fonction pour récupérer la couleur du plafond
void	get_ceiling_color(t_map *map, char *line)
{
	char	**colors;

	colors = ft_split(line + 2, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2])
		main_error("Invalid ceiling color format");
	map->color_ceiling = (ft_atoi(colors[0]) << 16) | (ft_atoi(colors[1]) << 8) | ft_atoi(colors[2]);
	free(colors[0]);
	free(colors[1]);
	free(colors[2]);
	free(colors);
}

void	get_colors(t_map *map, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		main_error("Failed to open file");
	while ((line = get_next_line(fd)) != NULL)
	{
		if (ft_strncmp(line, "F ", 2) == 0)
			get_floor_color(map, line);
		else if (ft_strncmp(line, "C ", 2) == 0)
			get_ceiling_color(map, line);
		free(line);
	}
	close(fd);
}
