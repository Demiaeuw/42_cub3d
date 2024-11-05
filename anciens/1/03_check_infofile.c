/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_check_infofile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 00:20:29 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/29 16:48:50 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	check_infofile(char *filename)
{
	check_file_empty(filename);
	check_pathfile(filename);
	check_colors(filename);
	check_map_presence(filename);
}

// Fonction qui check si le fichier n'est pas vide
void	check_file_empty(char *filename)
{
	int		fd;
	char	buffer[1];

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		main_error("Failed to open file");
	if (read(fd, buffer, 1) == 0)
	{
		close(fd);
		main_error("File is empty. A valid map file must contain data.");
	}
	close(fd);
}

// Fonction qui check si le fichier contient les paths
void	check_pathfile(char *filename)
{
	//verifier que les path son bien des .xpm
	int		fd;
	char	*line;
	int		north_found = 0;
	int		south_found = 0;
	int		east_found = 0;
	int		west_found = 0;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		main_error("Failed to open file");
	while ((line = get_next_line(fd)) != NULL)
	{
		char *trimmed_line = ft_strtrim(line, " \t");
		if ((ft_strncmp(trimmed_line, "NO ", 3) == 0 ) ||
			(ft_strncmp(trimmed_line, "SO ", 3) == 0 ) ||
			(ft_strncmp(trimmed_line, "EA ", 3) == 0 ) ||
			(ft_strncmp(trimmed_line, "WE ", 3) == 0 ))
		{
			if (ft_strncmp(trimmed_line, "NO ", 3) == 0)
				north_found = 1;
			else if (ft_strncmp(trimmed_line, "SO ", 3) == 0)
				south_found = 1;
			else if (ft_strncmp(trimmed_line, "EA ", 3) == 0)
				east_found = 1;
			else if (ft_strncmp(trimmed_line, "WE ", 3) == 0)
				west_found = 1;
		}
		
		free(trimmed_line);
		free(line);
	}
	close(fd);
	if (!north_found || !south_found || !east_found || !west_found)
		main_error("Missing or incorrect texture paths. All four texture paths (North, South, East, West) must be specified with valid paths.");
}

// Fonction qui vérifie que les couleurs sont presente et au bon format 
void	check_colors(char *filename)
{
	int		fd;
	char	*line;
	int		floor_found = 0;
	int		ceiling_found = 0;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		main_error("Failed to open file");
	while ((line = get_next_line(fd)) != NULL)
	{
		if (ft_strncmp(line, "F ", 2) == 0)
		{
			floor_found = 1;
			char **colors = ft_split(line + 2, ',');
			if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
				main_error("Invalid floor color format. Expected format: F R,G,B");
			if (ft_atoi(colors[0]) < 0 || ft_atoi(colors[0]) > 255 ||
				ft_atoi(colors[1]) < 0 || ft_atoi(colors[1]) > 255 ||
				ft_atoi(colors[2]) < 0 || ft_atoi(colors[2]) > 255)
				main_error("Invalid floor color values. Each value must be between 0 and 255.");
			free(colors[0]);
			free(colors[1]);
			free(colors[2]);
			free(colors);
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			ceiling_found = 1;
			char **colors = ft_split(line + 2, ',');
			if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
				main_error("Invalid ceiling color format. Expected format: C R,G,B");
			if (ft_atoi(colors[0]) < 0 || ft_atoi(colors[0]) > 255 ||
				ft_atoi(colors[1]) < 0 || ft_atoi(colors[1]) > 255 ||
				ft_atoi(colors[2]) < 0 || ft_atoi(colors[2]) > 255)
				main_error("Invalid ceiling color values. Each value must be between 0 and 255.");
			free(colors[0]);
			free(colors[1]);
			free(colors[2]);
			free(colors);
		}
		free(line);
	}
	close(fd);
	if (!floor_found || !ceiling_found)
		main_error("Missing color definitions. Both floor and ceiling colors must be specified.");
}

// Fonction qui check si la map est presente
void	check_map_presence(char *filename)
{
	int		fd;
	char	*line;
	int		map_found = 0;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		main_error("Failed to open file");
	while ((line = get_next_line(fd)) != NULL)
	{
		char *trimmed_line = ft_strtrim(line, " \t");
		if (trimmed_line[0] == '1' || trimmed_line[0] == '0')
			map_found = 1;
		free(trimmed_line);
		free(line);
		if (map_found)
			break;
	}
	close(fd);
	if (!map_found)
		main_error("Missing map data. A valid map must be present in the file.");
}
