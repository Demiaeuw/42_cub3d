/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_color-gestion_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:39:06 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/30 20:19:40 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	rgb_to_hex(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

void	add_floor_color(char *filename, t_game **game)
{
	
}