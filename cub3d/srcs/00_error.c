/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:42:58 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/16 17:11:09 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	main_error(char *str)
{
	printf("\n\033[31mError\033[0m\n\n");
	printf("%s\n", str);
	//ajouter les free au besoin
	exit(EXIT_FAILURE);
}
