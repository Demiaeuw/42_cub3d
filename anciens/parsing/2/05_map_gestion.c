/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_map_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:27:49 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/05 14:42:34 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	map_gestion(char **filename, t_game **game)
{
	
}

// Fonction pour vérifier si une ligne est une ligne de carte valide
int	is_map_line(char *line)
{
	int i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' &&
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}


// Fonction pour ajouter la carte dans game->map->tab
void add_map(char *filename, t_game *game)
{
	int		file;
	char	*line;
	int		is_map_section;
	int		i;

	line = NULL;
	is_map_section = 0;
	i = 0;
	file = open(filename, O_RDONLY);
	game->map->tab = malloc(sizeof(char *) * (game->map->height + 1));
	if (!game->map->tab)
		message_error("Failed to allocate memory for map");
	while (get_next_line(file, &line) > 0)
	{
		if (is_map_line(line) && !is_map_section)
			is_map_section = 1;
		if (is_map_section)
		{
			game->map->tab[i++] = ft_strdup(line);
			game->map->width = ft_max(game->map->width, ft_strlen(line));
		}
		free(line);
	}
	game->map->tab[i] = NULL;
	game->map->height = i;
	close(file);
}

// Fonction pour compter les lignes de la carte
int count_map_lines(char *filename)
{
    int		file;
    char	*line = NULL;
    int		count = 0;
    int		is_map_section = 0;

	line = NULL;
	count = 0;
	is_map_section = 0;
    file = open(filename, O_RDONLY);
    while (get_next_line(file, &line) > 0)
    {
        if (is_map_line(line))
        {
            if (!is_map_section)
                is_map_section = 1;
            count++;
        }
        else if (is_map_section && !is_map_line(line))
            break ;
        free(line);
    }
    close(file);
    return count;
}