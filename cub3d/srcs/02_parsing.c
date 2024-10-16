/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:43:20 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/16 17:29:52 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	main_mapcheck(t_map *map)
{
	check_infomap(map);			//verif qu'il y est bien toutes les infos de map 1 : adresses des textures / 2. code couleur floor et celing / 3. la map
	check_mapcontent(map);		//verif si que des 0 1 N0 S E W ou des espaces a l'exterieur de la map (attention que la map, pas les infos de la map)
	check_wall(map);			//verif que la map est entouré de 1
}
