/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:43:20 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/02 18:41:20 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	main_mapcheck(t_map *map)
{
	check_infomap(map);			//verif qu'il y est bien toutes les infos de map 1 : adresses des textures / 2. code couleur floor et celing / 3. la map
	check_mapcontent(map);		//verif si que des 0 1 N S E W (attention que la map, pas les infos de la map)
	check_wall(map);			//verif que la map est entouré de 1
}

void	check_mapcontent(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->tab[i])
	{
		j = 0;
		while (map->tab[i][j] != '\0')
		{
			if (map->tab[i][j] != WALL
				&& map->tab[i][j] != GROUND
				&& map->tab[i][j] != NORTH
				&& map->tab[i][j] != SOUTH
				&& map->tab[i][j] != EAST
				&& map->tab[i][j] != WEST
				&& map->tab[i][j] != '\n'
				&& map->tab[i][j] != '\r')
				main_error("map content");
			j++;
		}
		i++;
	}
}
