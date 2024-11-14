/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_color_gestion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:09:43 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/14 19:56:06 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	convert_rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	trim_trailing_whitespace(char *str)
{
	int	len;

	len = strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n'
			|| str[len - 1] == '\t'))
	{
		str[len - 1] = '\0';
		len--;
	}
}

int	validate_and_parse_color(char *color_str)
{
	int		r;
	int		g;
	int		b;
	char	*endptr;

	trim_trailing_whitespace(color_str);
	r = ft_strtol(color_str, &endptr, 10);
	if (*endptr != ',' || r < 0 || r > 255)
		return (-1);
	color_str = endptr + 1;
	g = ft_strtol(color_str, &endptr, 10);
	if (*endptr != ',' || g < 0 || g > 255)
		return (-1);
	color_str = endptr + 1;
	b = ft_strtol(color_str, &endptr, 10);
	if (*endptr != '\0' || b < 0 || b > 255)
		return (-1);
	return (convert_rgb_to_hex(r, g, b));
}

void	check_set_color(char *line, int *color, int *is_set, char *type)
{
	if (ft_strncmp(line, type, 2) == 0 && !*is_set)
	{
		*color = validate_and_parse_color(line + 2);
		if (*color == -1)
			message_error("Invalid color format", NULL);
		*is_set = 1;
	}
}

void	color_gestion(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	int		floor_set;
	int		ceiling_set;

	floor_set = 0;
	ceiling_set = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		message_error("Failed to open file", game);
	line = get_next_line(fd);
	while (line != NULL)
	{
		check_set_color(line, &game->map->color_floor, &floor_set, "F ");
		check_set_color(line, &game->map->color_ceiling, &ceiling_set, "C ");
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!floor_set || !ceiling_set)
		message_error("Missing floor or ceiling color in file", game);
}
