/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_second_calque.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:12:43 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/16 17:23:37 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	render_walls(t_game *game)
{
	int	column;

	column = 0;
	while (column < game->screen_width)
	{
		init_ray(game, column);
		init_step_and_side_dist(game);
		perform_dda(game);
		calculate_perp_dist(game);
		render_column(game, column);
		column++;
	}
}

void	calculate_perp_dist(t_game *game)
{
	if (game->dda->side == 0)
	{
		game->col_data->perp_dist = (game->dda->map_x - game->player->x \
			+ (1 - game->dda->step_x) / 2) / game->col_data->ray_dir_x;
	}
	else
	{
		game->col_data->perp_dist = (game->dda->map_y - game->player->y \
			+ (1 - game->dda->step_y) / 2) / game->col_data->ray_dir_y;
	}
}

void    render_column(t_game *game, int column)
{
	int line_height;
	int draw_start;
	int draw_end;
	int y;
	int tex_x, tex_y;
	int texture_id;
	float wall_hit; // Position de l'impact sur le mur (pour tex_x)
	float step;     // Pas pour avancer dans la texture
	float tex_pos;  // Position Y dans la texture
	int color;

	// Calcul de la hauteur de la colonne
	line_height = (int)(game->screen_height / game->col_data->perp_dist);
	draw_start = -line_height / 2 + game->screen_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + game->screen_height / 2;
	if (draw_end >= game->screen_height)
		draw_end = game->screen_height - 1;

	// Identifier la texture à utiliser
	if (game->dda->hit_direction == 'N')
		texture_id = 0; // Texture Nord
	else if (game->dda->hit_direction == 'S')
		texture_id = 1; // Texture Sud
	else if (game->dda->hit_direction == 'E')
		texture_id = 2; // Texture Est
	else
		texture_id = 3; // Texture Ouest

	// Calcul de la position de l'impact sur le mur
	if (game->dda->side == 0)
		wall_hit = game->player->y + game->col_data->perp_dist * game->col_data->ray_dir_y;
	else
		wall_hit = game->player->x + game->col_data->perp_dist * game->col_data->ray_dir_x;
	wall_hit -= floor(wall_hit);

	// Calcul de tex_x (coordonnée X dans la texture)
	tex_x = (int)(wall_hit * 64); // Remplace 64 par la largeur réelle de la texture
	if ((game->dda->side == 0 && game->col_data->ray_dir_x > 0) ||
		(game->dda->side == 1 && game->col_data->ray_dir_y < 0))
		tex_x = 64 - tex_x - 1; // Inverse si nécessaire

	// Initialisation de tex_pos (position Y initiale dans la texture)
	step = 64.0 / line_height; // Pas entre chaque pixel (64 = hauteur de la texture)
	tex_pos = (draw_start - game->screen_height / 2 + line_height / 2) * step;

	// Dessine chaque pixel de la colonne
	y = draw_start;
	while (y <= draw_end) {
		// Calcul de tex_y (coordonnée Y dans la texture)
		tex_y = (int)tex_pos & 63; // 63 = hauteur de la texture - 1
		tex_pos += step;

		// Récupère la couleur de la texture
		color = game->texture[texture_id][tex_y * 64 + tex_x]; // Remplace 64 par la largeur réelle de la texture

		// Dessine le pixel dans le buffer
		*((unsigned int *)(game->addr + (y * game->line_length + column * (game->bpp / 8)))) = color;
		y++;
	}
}


void	init_ray(t_game *game, int column)
{
	float	camera_x;


	camera_x = 2 * ((float)column / (float)game->screen_width) - 1;

	game->col_data->ray_dir_x = game->player->dir_x \
		+ game->player->cam_x * camera_x;
	game->col_data->ray_dir_y = game->player->dir_y \
		+ game->player->cam_y * camera_x;

	game->dda->map_x = (int)game->player->x;
	game->dda->map_y = (int)game->player->y;
}
