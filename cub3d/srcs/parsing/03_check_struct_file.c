/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_check_struct_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:55:45 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/21 05:10:53 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * Vérifie que la carte est le dernier élément du fichier `.cub`.
 * Si des éléments sont présents après la carte ou si aucune carte n'est trouvée,
 * affiche un message d'erreur et quitte le programme.
 */
void	check_struct_file(char *filename)
{
	int		fd;
	char	*line;
	int		found_map;

	found_map = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		message_error("Failed to open file", NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*line == '1' || *line == '0')
			found_map = 1;
		else if (found_map && *line != '\0')
		{
			free(line);
			close(fd);
			message_error("Map is not the last element", NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!found_map)
		message_error("Map not found in file", NULL);
}
