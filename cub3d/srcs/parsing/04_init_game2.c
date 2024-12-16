/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_init_game2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:47:32 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/16 18:09:02 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

t_render_colomn_data	*init_render_colomn_data(void)
{
	t_render_colomn_data	*rend_coldata;
	
	rend_coldata = (t_render_colomn_data *)malloc(sizeof(t_render_colomn_data));
	if (!rend_coldata)
		return (NULL);
	rend_coldata->line_height = 0;
	rend_coldata->draw_start = 0;
	rend_coldata->draw_end = 0;
	rend_coldata->y = 0;
	rend_coldata->tex_x = 0;
	rend_coldata->tex_y = 0;
	rend_coldata->texture_id = 0;
	rend_coldata->wall_hit = 0.0;
	rend_coldata->step = 0.0;
	rend_coldata->tex_pos = 0.0;
	rend_coldata->color = 0;
	return (rend_coldata);
}
/**
 * Initialise la structure `t_game` qui contient toutes les données du jeu,
 * incluant les informations de texture (`t_info`), la carte (`t_map`),
 * et le joueur (`t_player`). Vérifie que chaque sous-structure est correctement
 * allouée et initialise également MinilibX et la fenêtre. En cas d'erreur
 * d'initialisation ou d'allocation, libère les ressources et retourne NULL.
 */
t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->infos = init_info();
	game->map = init_map();
	game->player = init_player();
	game->dda = init_dda();
	game->col_data = init_col_data();
	game->rendcoldata = init_render_colomn_data();
	game->texture = NULL;
	game->screen_width = 800;
	game->screen_height = 600;
	game->win = NULL;
	game->mlx = NULL;
	if (!game->infos || !game->map || !game->player)
	{
		cleanup_and_exit(game);
		return (NULL);
	}
	init_game_two(game);
	return (game);
}

void	init_game_two(t_game *game)
{
	game->img = NULL;
	game->addr = NULL;
	game->bpp = 0;
	game->line_length = 0;
	game->endian = 0;
}
