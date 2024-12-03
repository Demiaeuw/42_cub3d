/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:08:43 by acabarba          #+#    #+#             */
/*   Updated: 2024/12/03 18:08:57 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"
int	render(t_game *game)
{
	// Afficher la minimap
	render_minimap(game);

	// Vous pouvez aussi ajouter des rendus pour la fenêtre principale
	// render_game(game);

	return (0);
}