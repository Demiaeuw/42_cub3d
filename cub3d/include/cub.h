/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:39:46 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/07 14:13:01 by acabarba         ###   ########.fr       */
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
# include "minilibx-linux/mlx_int.h"

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
	int		height;
	int		color_floor;
	int		color_ceiling;
	char	direction_start;
	int		position_start_x;
	int		position_start_y;
	int		player_count;
}	t_map;

// structure principale 
typedef struct s_game
{
	t_info	*infos;
	t_map	*map;
	// ajout mlx
	// ajouter les controles
}	t_game;

//PARSING
void	message_error(char *str);
void	main_parsing(int ac, char **av, t_game **game);
void	check_argument(int i);
void	check_fileextension(char *filename);
void	check_file(char *filename);
void	check_struct_file(char *filename);
t_info	*init_info(void);
t_map	*init_map(void);
t_game	*init_game(void);
int		check_extension(char *path);
void	set_texture_path(char **destination, char *path);
void	remove_newline(char *line);
void	path_gestion(char *filename, t_game *game);
int		convert_rgb_to_hex(int r, int g, int b);
void	trim_trailing_whitespace(char *str);
int		validate_and_parse_color(char *color_str);
void	color_gestion(char *filename, t_game *game);
void	map_gestion(char *filename, t_game *game);
int		is_valid_map_character(char c);
void	validate_map_line(char *line);
void	check_map_characters(char *filename);
int		count_map_lines(int fd);
void	init_map_space(char *filename, t_game *game);
void	copy_map_line(t_game *game, char *line, int i, int fd);
void	fill_map_tab(int fd, t_game *game);
void	copy_map(char *filename, t_game *game);
void	check_adjacent(char **tab, int x, int y, int height);
void	check_map_surrounded_by_walls(t_game *game);
int		is_player_character(char c);
void	check_player_position(t_map *map);
void	update_player_position(char c, int x, int y, t_map *map);
void	validate_and_save_player_position(t_map *map);
void	validate_and_save_player_position(t_map *map);

void 	print_info(t_info *infos);
void	print_map_layout(char **tab);
void 	print_map(t_map *map);
void 	print_game_info(t_game *game);

#endif