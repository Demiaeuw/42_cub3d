/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_color_gestion_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:39:06 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/04 17:02:41 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void    add_color(char *filename, t_game **game)
{
    add_floor_color(filename, game);
    add_ceiling_color(filename, game);
}

int	rgb_to_hex(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

void	free_rgbtab(char **rgbtab)
{
    int	i;

    i = 0;
    while (rgbtab[i])
        free(rgbtab[i++]);
    free(rgbtab);
}

/**
 * Recuperaton des la couleur du sol
*/
void	process_floor_color(char *colors, t_game **game)
{
    char	**rgbtab;
    int		r;
    int		g;
    int		b;

    rgbtab = ft_split(colors, ',');
    if (!rgbtab || !rgbtab[0] || !rgbtab[1] || !rgbtab[2])
        message_error("Invalid floor color format");
    r = ft_atoi(rgbtab[0]);
    g = ft_atoi(rgbtab[1]);
    b = ft_atoi(rgbtab[2]);
    free_rgbtab(rgbtab);
    (*game)->map->color_floor = rgb_to_hex(r, g, b);
}

void	add_floor_color(char *filename, t_game **game)
{
    int		file;
    char	buffer[BUFFER_SIZE];
    char	line[BUFFER_SIZE];
    int		i;
    int     j;
    ssize_t	bytes_read;

    file = open(filename, O_RDONLY);
    i = 0;
    while ((bytes_read = read(file, buffer, BUFFER_SIZE - 1)) > 0)
    {
        j = -1;
        while (++j < bytes_read)
        {
            if (buffer[j] == '\n' || i >= BUFFER_SIZE - 1)
            {
                line[i] = '\0';
                i = 0;
                if (ft_strncmp(line, "F ", 2) == 0)
                {
                    process_floor_color(line + 2, game);
                    close(file);
                    return;
                }
            }
            else
                line[i++] = buffer[j];
        }
    }
    close(file);
}

void	process_ceiling_color(char *colors, t_game **game)
{
    char	**rgbtab;
    int		r;
    int		g;
    int		b;

    rgbtab = ft_split(colors, ',');
    if (!rgbtab || !rgbtab[0] || !rgbtab[1] || !rgbtab[2])
        message_error("Invalid ceiling color format");
    r = ft_atoi(rgbtab[0]);
    g = ft_atoi(rgbtab[1]);
    b = ft_atoi(rgbtab[2]);
    free_rgbtab(rgbtab);
    (*game)->map->color_ceiling = rgb_to_hex(r, g, b);
}

void	add_ceiling_color(char *filename, t_game **game)
{
    int		file;
    char	buffer[BUFFER_SIZE];
    char	line[BUFFER_SIZE];
    int		i;
    int     j;
    ssize_t	bytes_read;

    file = open(filename, O_RDONLY);
    i = 0;
    while ((bytes_read = read(file, buffer, BUFFER_SIZE - 1)) > 0)
    {
        j = -1;
        while (++j < bytes_read)
        {
            if (buffer[j] == '\n' || i >= BUFFER_SIZE - 1)
            {
                line[i] = '\0';
                i = 0;
                if (ft_strncmp(line, "C ", 2) == 0)
                {
                    process_ceiling_color(line + 2, game);
                    close(file);
                    return;
                }
            }
            else
                line[i++] = buffer[j];
        }
    }
    close(file);
}
