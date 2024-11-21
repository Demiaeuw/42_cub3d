/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_check_argument.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:53:07 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/21 05:10:31 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * Vérifie que le programme reçoit exactement deux arguments.
 * Affiche un message d'erreur et quitte si ce n'est pas le cas.
 */

void	check_argument(int i)
{
	if (i != 2)
		message_error("Usage : ./cub3d <map_file.cub>", NULL);
}

/**
 * Vérifie que le fichier possède une extension valide `.cub`.
 * Affiche un message d'erreur et quitte si l'extension est incorrecte.
 */

void	check_fileextension(char *filename)
{
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (dot == NULL || *(dot + 1) == '\0' || ft_strcmp(dot + 1, "cub") != 0)
		message_error("Invalid file extension. The file must have .cub", NULL);
}

/**
 * Vérifie que le fichier est accessible, possède une extension `.cub` valide,
 * et n'est pas vide. Affiche un message d'erreur et quitte en cas d'échec.
 */

void	check_file(char *filename)
{
	int		file;
	char	buffer[1];
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (dot == NULL || *(dot + 1) == '\0' || ft_strcmp(dot + 1, "cub") != 0)
		message_error("Invalid file extension. The file must have .cub", NULL);
	file = open(filename, O_RDONLY);
	if (file == -1)
		message_error("Failed to open file", NULL);
	if (read(file, buffer, 1) == 0)
	{
		close(file);
		message_error("The file is empty", NULL);
	}
	close(file);
}
