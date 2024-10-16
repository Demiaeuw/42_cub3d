/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:39:46 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/16 18:32:31 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>

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
typedef struct s_map //peut etre pour diviser les infos passé par une liste chainé ?
{
	char	**tab;
	int		width;
	int		heinght
}	t_map;

// structure principale 
typedef struct s_game
{
	t_info	*infos;
	t_map	*map;
	// ajout mlx
	// ajouter les controles
}	t_game;

void	main_error(char *str);
void	main_mapcheck(t_map *map);

#endif