/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:39:46 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/29 16:01:29 by acabarba         ###   ########.fr       */
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

# ifdef __linux__
#  include <X11/X.h>
#  include <X11/keysym.h>
# elif __APPLE__
#  include <ApplicationServices/ApplicationServices.h>
# endif

# ifndef BUFFER_SIZE_GNL
#  define BUFFER_SIZE_GNL 10
# endif

# define WALL '1'
# define GROUND '0'
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'

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

//utils
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_dup(char *src);
int			split_count_word(char *str, char sep);
char		**split_create_tab(char *str, char sep, char **dest);
char		**ft_split(char const *s, char c);
size_t		ft_strlen(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);
void		ft_putnbr_fd(long n, int fd);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strchr(const char *s, int c);

//gnl
char		*get_next_line(int fd);
char		*gnl_ad_to_stash(int fd, char *stash);
char		*gnl_line(char *stash);
char		*create_new_stash(char *stash, int i);
char		*gnl_clean_static(char *stash);
char		*gnl_strchr(const char *s, int c);
size_t		gnl_strlen(const char *c);
void		gnl_bzero(void *s, size_t n);
void		*gnl_calloc(size_t nmemb, size_t size);
char		*gnl_strjoin(char *s1, char *s2);
// utils_parsing
void		display_parsed_info(char *filename, t_game *game);
void		display_texture_info(t_game *game);
void		display_color_info(t_game *game);
void		display_map_info(t_game *game);

//---------------------------------------------------------//
//00
void		main_error(char *str);
void		main_free(t_game *game);

//01
void 		main_parsing(int ac, char **av, t_game *game);
void		initialize_game(t_game *game);
int			check_file_extension(char *filename);
int			get_map_size(char *filename);

//02
void 		parsing_file(char *filename, t_game *game);
void		get_texture_paths(t_info *infos, char *filename);
void		verify_texture_paths(t_info *infos, char *filename);
long		get_floor_color(char *line);
long		get_ceiling_color(char *line);
void		get_colors(t_map *map, char *filename);
int			get_map_width(char *filename);
void		get_map(t_map *map, char *filename);
void		open_file(t_map *map, char *filename, int *fd);

//03
void		check_infofile(char *filename);
void		check_file_empty(char *filename);
void		check_pathfile(char *filename);
void		check_colors(char *filename);
void		check_map_presence(char *filename);

//04
void		check_mapcontent(t_game *game);
void		validate_map_cell(char cell, int *count_player, t_map *map, int row, int col);
void		record_player_position(t_map *map, int row, int col, char player);
//04
int is_valid_neighbor(char **map, int row, int col, int max_width, int max_height);
void check_map(t_game *game);

//test 

#endif