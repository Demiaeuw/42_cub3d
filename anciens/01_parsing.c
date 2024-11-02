/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:43:20 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/29 16:23:38 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	main_parsing(int ac, char **av, t_game *game)
{
	if (ac != 2)  																// Vérification du nombre d'arguments
		main_error("Usage : ./cub3d <map_file.cub>");
	if (!check_file_extension(av[1])) 
		main_error("Invalid file extension. The file must have a .cub");  		// Vérification de l'extension du fichier

	check_infofile(av[1]);  													// Vérification des informations dans le fichier 
	parsing_file(av[1], game); 													// Ajout des infos aux structures
	display_map_info(game);
	check_mapcontent(game);  												// Vérification du contenu de la map
	display_parsed_info(av[1], game);  											// Affichage du parsing
}

// Fonction d'initialisation des malloc
void	initialize_game(t_game *game)
{
	game->infos = malloc(sizeof(t_info));
	if (!game->infos)
		main_error("Memory allocation failed for infos");

	game->map = malloc(sizeof(t_map));
	if (!game->map)
		main_error("Memory allocation failed for map");

	game->infos->path_north = NULL;
	game->infos->path_south = NULL;
	game->infos->path_west = NULL;
	game->infos->path_east = NULL;
	
	game->map->tab = NULL;
	game->map->width = 0;
	game->map->height = 0;
	game->map->color_floor = 0;
	game->map->color_ceiling = 0;
	game->map->direction_start = '\0';
	game->map->position_start_x = -1;
	game->map->position_start_y = -1;
}

// Fonction qui vérifie si le fichier passé en argument a bien l'extension .cub
int	check_file_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (filename[len - 4] == '.' && filename[len - 3] == 'c' &&
		filename[len - 2] == 'u' && filename[len - 1] == 'b')
		return (1);
	return (0);
}

// Fonction pour calculer la taille de la carte
int get_map_size(char *filename)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		main_error("Failed to open file");

	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] == '1' || line[0] == '0')
			count++;
		free(line);
	}
	close(fd);
	return count;
}
