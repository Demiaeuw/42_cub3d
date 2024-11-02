/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:56:10 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/30 10:56:25 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	check_argument(int i)
{
	if (i != 2)
		message_error("Usage : ./cub3d <map_file.cub>");
}

void	check_fileextension(char *filename)
{
	char *dot;

	dot = ft_strrchr(filename, '.');
	if (dot == NULL || *(dot + 1) == '\0' || ft_strcmp(dot + 1, "cub") != 0)
		message_error("Invalid file extension. The file must have a .cub");
}

void	check_file(char *filename)
{
	int		file;
	char	buffer[1];
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (dot == NULL || *(dot + 1) == '\0' || ft_strcmp(dot + 1, "cub") != 0)
		message_error("Invalid file extension. The file must have a .cub");
	file = open(filename, O_RDONLY);
	if (file == -1)
		message_error("Failed to open file");
	if(read(file, buffer, 1) == 0)
	{
		close(file);
		message_error("The file is empty");
	}
	close(file);
}
