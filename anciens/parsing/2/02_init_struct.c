/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:00:58 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/30 11:11:25 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	init_game(t_game **game)
{
	*game = malloc(sizeof(t_game));
	if (*game == NULL)
	{
		message_error("failed to allocate memory for t_game");
	}
	init_info(&(*game)->infos);
	init_map(&(*game)->map);
}

void	init_info(t_info **info)
{
	*info = malloc(sizeof(t_info));
	if (*info == NULL)
	{
		//free ici les struct deja créer
		message_error("failed to allocate memory for t_info");
	}
	(*info)->path_north = NULL;
	(*info)->path_south = NULL;
	(*info)->path_east = NULL;
	(*info)->path_west = NULL;
}

void	init_map(t_map **map)
{
	*map = malloc(sizeof(t_map));
	if (*map == NULL)
	{
		//free ici les struct deja créer
		message_error("failed to allocate memory for t_map");
	}
	(*map)->tab = NULL;
	(*map)->width = 0;
	(*map)->height = 0;
	(*map)->color_ceiling = 0;
	(*map)->color_floor = 0;
	(*map)->direction_start = 'N';
	(*map)->position_start_x = 0;
	(*map)->position_start_y = 0;
}
