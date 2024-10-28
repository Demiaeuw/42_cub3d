/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parsing_file01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:25:03 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/28 09:50:06 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void parsing_file(char *filename, t_game *game)
{
	get_texture_paths(game->infos, filename);									// Récupération des chemins des textures
	verify_texture_paths(game->infos, filename);
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

// Fonction qui verifie si les paths on bien ete copie (neednorme)
void	verify_texture_paths(t_info *infos, char *filename)
{
	int fd;
	char *line;

	fd = open(filename, O_RDONLY);
	if (fd == -1) 
		main_error("Failed to open file for verification");
	while ((line = get_next_line(fd)) != NULL)
	{
		char *trimmed_line = ft_strtrim(line, " \t\n");
		
		if (ft_strncmp(trimmed_line, "NO ", 3) == 0)
		{
			if (ft_strncmp(infos->path_north, trimmed_line + 3, ft_strlen(trimmed_line + 3)) != 0)
				main_error("Mismatch in North texture path during parsing");
		}
		else if (ft_strncmp(trimmed_line, "SO ", 3) == 0)
		{
			if (ft_strncmp(infos->path_south, trimmed_line + 3, ft_strlen(trimmed_line + 3)) != 0)
				main_error("Mismatch in South texture path during parsing");
		}
		else if (ft_strncmp(trimmed_line, "WE ", 3) == 0)
		{
			if (ft_strncmp(infos->path_west, trimmed_line + 3, ft_strlen(trimmed_line + 3)) != 0)
				main_error("Mismatch in West texture path during parsing");
		}
		else if (ft_strncmp(trimmed_line, "EA ", 3) == 0)
		{
			if (ft_strncmp(infos->path_east, trimmed_line + 3, ft_strlen(trimmed_line + 3)) != 0)
				main_error("Mismatch in East texture path during parsing");
		}
		free(trimmed_line);
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
