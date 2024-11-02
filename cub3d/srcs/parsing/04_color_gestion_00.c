/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_color_gestion_00.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:21:11 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/30 20:15:37 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	color_gestion(char *filename, t_game **game)
{
	//verifier la presence de deux couleurs
	//verification du format des 2 couleurs
	check_color(filename);
	//ajout + mise au format des 2 couleurs pour la mlx
	add_color(filename, game);
}


void	check_color(char *filename)
{
	if (check_color_presence(filename) != 2)
	{
		//free struct
		message_error("Missing color definition for ceiling or floor");
	}
}

int	check_color_presence(char *filename)
{
	int		file;
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	int		has_color;
	int		i;

	i = 0;
	has_color = 0;
	file = open(filename, O_RDONLY);
	while ((bytes_read = read(file, &buffer[i], 1)) > 0)
	{
		if (buffer[i] == '\n' || i >= BUFFER_SIZE - 1)
		{
			buffer[i] = '\0';
			if (strncmp(buffer, "C ", 2) == 0 || strncmp(buffer, "F ", 2) == 0)
				has_color++;
			i = 0;
		}
		else
			i++;
	}
	close(file);
	return (has_color);
}

int	check_rgb_format(const char *line)
{
	int		i;
	int		count;
	char	value[4];
	int		j;

	i = 0;
	count = 0;
	while (line[i] && line[i] != ' ')
		i++;
	i++;
	while (line[i] && count < 3)
	{
		j = 0;
		while (line[i] && line[i] != ',' && j < 3)
		{
			if (!ft_isdigit(line[i]))
				return (0);
			value[j++] = line[i++];
		}
		value[j] = '\0';
		if (!is_valid_rgb_value(value))
			return (0);
		count++;
		if (line[i] == ',')
			i++;
	}
	return (count == 3 && line[i] == '\0');
}

void	check_color_format(char *filename)
{
	int		file;
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	int		i;

	i = 0;
	file = open(filename, O_RDONLY);
	while ((bytes_read = read(file, &buffer[i], 1)) > 0)
	{
		if (buffer[i] == '\n' || i >= BUFFER_SIZE - 1)
		{
			buffer[i] = '\0';
			if ((strncmp(buffer, "C ", 2) == 0 || strncmp(buffer, "F ", 2) == 0)
				&& !check_rgb_format(buffer))
			{
				close(file);
				//free struct
				message_error("Invalid color format");
			}
			i = 0;
		}
		else
			i++;
	}
	close(file);
}