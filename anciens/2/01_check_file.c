/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:56:10 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/04 16:36:44 by acabarba         ###   ########.fr       */
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

int		its_map(char *line)
{
	int	i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] != ' '
			&& line[i] != '1'
			&& line[i] != '0'
			&& line[i] != 'N'
			&& line[i] != 'S'
			&& line[i] != 'E'
			&& line[i] != 'W')
			return (0);
		return (1);
	}
}

void	check_struct_file(char *filename)
{
	int		file;
	char	buffer[BUFFER_SIZE];
	int		map_start;
	ssize_t	bytes_read;
	int		bytes_read;
	char	*line_start;
	char	*line_end;
	
	file = open(filename, O_RDONLY);
	
	map_start = 0;
	while ((bytes_read = read(file, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		line_start = buffer;\
		while ((line_end = ft_strchr(line_start, '\n')) != NULL)
		{
			*line_end = '\0';
			if (!map_start)
			{
				if (its_map(line_end))
					map_start = 1;
			}
			else
			{
				if (ft_strlen(line_start) > 0 && !its_map(line_end))
					message_error("Extra content found after map");
			}
			line_start = line_end + 1;
		}
		if (map_start && *line_start != '\0' && !its_map(line_start))
		{
			close(file);
			message_error("Extra content found after map");
		}
	}
	close(file);
}
