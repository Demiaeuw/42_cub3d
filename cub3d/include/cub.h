/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:39:46 by acabarba          #+#    #+#             */
/*   Updated: 2025/01/03 16:39:26 by kpourcel         ###   ########.fr       */
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
# include <math.h>
# include "../srcs/utils/libft/libft.h"
# include "minilibx-linux/mlx_int.h"
# include "minilibx-linux/mlx.h"

# ifdef __linux__
#  include <X11/X.h>
#  include <X11/keysym.h>
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_ESC 65307
# elif __APPLE__
#  include <ApplicationServices/ApplicationServices.h>
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT
#  define KEY_RIGHT
#  define KEY_UP
#  define KEY_DOWN
#  define KEY_ESC 53
# endif

# define TEXTURE_WIDTH 256
# define TEXTURE_HEIGHT 256
# define PADDING 0.3
# define GREEN "\033[32m"
# define RESET "\033[0m"

# define BUFFER_SIZE 1024
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_info
{
	char	*path_north;
	char	*path_south;
	char	*path_east;
	char	*path_west;
}	t_info;

typedef struct s_map
{
	char	**tab;
	int		height;
	int		color_floor;
	int		color_ceiling;
	char	dir_start;
	int		position_start_x;
	int		position_start_y;
	int		player_count;
}	t_map;

typedef struct s_player
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	cam_x;
	float	cam_y;
	int		w;
	int		a;
	int		s;
	int		d;
	int		up;
	int		left;
	int		down;
	int		right;
}	t_player;

typedef struct s_dda
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		side;
	char	hit_direction;
}	t_dda;

typedef struct s_col_data
{
	int		column;
	float	ray_dir_x;
	float	ray_dir_y;
	float	perp_dist;
}	t_col_data;

typedef struct s_render_colomn_data
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		y;
	int		tex_x;
	int		tex_y;
	int		texture_id;
	float	wall_hit;
	float	step;
	float	tex_pos;
	int		color;
}	t_render_colomn_data;

typedef struct s_game
{
	t_info					*infos;
	t_map					*map;
	t_player				*player;
	t_dda					*dda;
	t_col_data				*col_data;
	t_render_colomn_data	*rendcoldata;
	void					*mlx;
	void					*win;
	void					**image_struct;
	int						**texture;
	int						screen_width;
	int						screen_height;
	int						**buffer;
	void					*img;
	char					*addr;
	int						bpp;
	int						line_length;
	int						endian;
}	t_game;

/* GAMEPLAY */
int						handle_key_press(int keycode, void *param);
void					handle_movement_keys(int keycode, t_game *game);
int						handle_key_release(int keycode, void *param);
int						can_move_to(char **map, float new_x, float new_y);
void					move_player(t_game *game, float delta_x, float delta_y);
void					process_mouvement(t_game *game);
void					rotate_camera(t_player *player, float angle);
void					handle_camera_rotation(t_game *game);

/* CLEANUP */
void					cleanup_resources(t_game *game);
void					cleanup_ressources_two(t_game *game);
void					cleanup_and_exit(t_game *game);
void					free_other_resources(t_game *game);
void					free_texture(t_game *game);
void					free_images(void *mlx, void **images, int size);
void					free_infos(t_info *infos);
void					free_window_and_display(t_game *game);

/* EVENTS */
int						handle_keypress(int keycode, t_game *game);
int						handle_close(t_game *game);

/* MINILIBX INITIALIZATION */
void					init_dela_mlx(t_game *game);
int						init_mlx_and_window(t_game *game);
void					free_textures(int **tab);
int						print_error(char *message);

/* TEXTURE HANDLING */
int						store_texture(t_game *game, int index, void *image);
int						exit_on_texture_failure(t_game *game, int loaded_count);
int						init_game_texture(t_game *game);
int						allocate_texture_resources(t_game *game);
int						load_single_texture(t_game *game, char *path,
							int index);
int						load_all_textures(t_game *game);
void					free_loaded_textures(void *mlx, void **textures,
							int count);
void					exit_cleanup(t_game *game);
int						exit_on_texture_failure(t_game *game, int loaded_count);

/* PARSING ERRORS */
void					message_error(char *str, t_game *game);
void					free_map_tab(t_map *map);
void					error_clean_exit(t_game *game);

/* PARSING INITIALIZATION */
void					main_parsing(int ac, char **av, t_game **game);
t_info					*init_info(void);
t_map					*init_map(void);
t_player				*init_player(void);
t_render_colomn_data	*init_render_colomn_data(void);
t_game					*init_game(void);
void					init_game_two(t_game *game);
t_dda					*init_dda(void);
t_col_data				*init_col_data(void);

/* FILE VALIDATION */
void					check_argument(int i);
void					check_fileextension(char *filename);
void					check_file(char *filename);
void					check_struct_file(char *filename);
int						check_extension(char *path);
void					set_texture_path(char **destination, char *path,
							t_game *game);
void					remove_newline(char *line);
void					path_gestion(char *filename, t_game *game);
int						file_exists(char *path);
void					check_texture_paths(t_game *game);

/* COLOR HANDLING */
int						convert_rgb_to_hex(int r, int g, int b);
void					trim_trailing_whitespace(char *str);
int						validate_and_parse_color(char *color_str);
void					check_set_color(char *line, int *color, int *is_set,
							char *type);
void					color_gestion(char *filename, t_game *game);

/* MAP HANDLING */
void					map_gestion(char *filename, t_game *game);
int						is_valid_map_character(char c);
void					validate_map_line(char *line, t_game *game);
void					check_map_characters(char *filename, t_game *game);
int						count_map_lines(int fd);
void					init_map_space(char *filename, t_game *game);
void					copy_map_line(t_game *game, char *line, int i, int fd);
void					fill_map_tab(int fd, t_game *game);
void					copy_map(char *filename, t_game *game);
int						check_adjacent(char **tab, int x, int y, int height);
void					check_map_surrounded_by_walls(t_game *game);

/* PLAYER VALIDATION */
int						is_player_character(char c);
void					check_player_position(t_game *game);
void					update_player_position(char c, int x, int y,
							t_game *game);
void					validate_and_save_player_position(t_game *game);
void					player_struct_start(t_game *game);
void					player_set_fov(t_player *player, float fov);

/* DEBUGGING AND PRINTING */
void					print_info(t_info *infos);
void					print_map_layout(char **tab);
void					print_player(t_player *player);
void					print_map(t_map *map);
void					print_texture_info(t_game *game);
void					print_dda(t_dda *dda);
void					print_col_info(t_col_data *col_data);
void					print_game(t_game *game);
void					print_game_info(t_game *game);
void					print_game_infos_two(t_game *game);

/* RAYCASTING RENDERING */
int						render(void *param);
void					init_image(t_game *game);
void					draw_floor_and_ceiling(t_game *game);
void					draw_floor(t_game *game);
void					draw_ceiling(t_game *game);

/* WALL RENDERING */
void					render_walls(t_game *game);
void					calculate_column_height(t_game *game);
void					determine_texture_id(t_game *game);
void					calculate_wall_hit(t_game *game);
void					calculate_texture_coordinates(t_game *game);
void					draw_column(t_game *game, int column);
void					render_column(t_game *game, int column);

/* RAYCASTING DDA */
void					init_ray(t_game *game, int column);
void					calculate_perp_dist(t_game *game);
void					update_dda_side_dist(t_dda *dda);
void					set_hit_direction(t_game *game);
void					perform_dda(t_game *game);

/* STEP AND SIDE DIST */
void					init_step_and_side_dist_x(t_game *game);
void					init_step_and_side_dist_y(t_game *game);
void					init_step_and_side_dist(t_game *game);

#endif