/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:39:46 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/04 16:37:09 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <limits.h>
# include "../srcs/utils/libft/libft.h"

# ifdef __linux__
#  include <X11/X.h>
#  include <X11/keysym.h>
# elif __APPLE__
#  include <ApplicationServices/ApplicationServices.h>
# endif

# define BUFFER_SIZE 1024

// infos des textures
typedef struct s_info
{
	char	*path_north;
	char	*path_south;
	char	*path_east;
	char	*path_west;
}	t_info;

// infos de la map
typedef struct s_map
{
	char	**tab;
	int		width;
	int		height;
	int		color_floor;
	int		color_ceiling;
	char	direction_start;
	int		position_start_x;
	int		position_start_y;
}	t_map;

// structure principale 
typedef struct s_game
{
	t_info	*infos;
	t_map	*map;
	// ajout mlx
	// ajouter les controles
}	t_game;

//--MESSAGES--//
//error
void	message_error(char *str);

//--PARSING--//
//00
void	main_parsing(int ac, char **av, t_game **game);
//01
void	check_argument(int i);
void	check_fileextension(char *filename);
void	check_file(char *filename);
int		its_map(char *line);
void	check_struct_file(char *filename);
//02
void	init_game(t_game **game);
void	init_info(t_info **info);
void	init_map(t_map **map);
//03
void	path_gestion(char *filename, t_game **game);
void	add_path(char *filename, t_game **game);
int		has_xpm(const char *path);
//04
void	color_gestion(char *filename, t_game **game);
void	check_color(char *filename);
int		check_color_presence(char *filename);
int		check_rgb_format(const char *line);
void	check_color_format(char *filename);
int		rgb_to_hex(int red, int green, int blue);
void	add_floor_color(char *filename, t_game **game);

#endif