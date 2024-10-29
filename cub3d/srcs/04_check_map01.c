/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_check_map01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:18:52 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/29 11:39:08 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

// Fonction qui vérifie si il y a des troue dans la map 
void flood_fill(char **tab, int x, int y, int height, int width, char target, char replacement)
{
    // Vérifier si la position est hors limites
    if (x < 0 || x >= height || y < 0 || y >= width)
        return;

    // Vérifier si la case est un mur, déjà remplie, ou non atteignable
    if (tab[x][y] == '1' || tab[x][y] == replacement || tab[x][y] == ' ' || tab[x][y] == '\t' || tab[x][y] == '\n' || tab[x][y] == '\r' || tab[x][y] == '\0')
        return;

    // Vérifier si la case n'a pas la couleur cible
    if (tab[x][y] != target && tab[x][y] != 'N' && tab[x][y] != 'S' && tab[x][y] != 'E' && tab[x][y] != 'W')
        return;

    // Remplacer la couleur
    printf("Remplir position (%d, %d)\n", x, y);
    tab[x][y] = replacement;

    // Propager aux voisins (haut, bas, gauche, droite)
    flood_fill(tab, x + 1, y, height, width, target, replacement);
    flood_fill(tab, x - 1, y, height, width, target, replacement);
    flood_fill(tab, x, y + 1, height, width, target, replacement);
    flood_fill(tab, x, y - 1, height, width, target, replacement);
}

void map_check_wall(char **tab, int start_x, int start_y)
{
    int i, j;
    int height = 0;
    int width;

    // Calculer la hauteur de la carte
    while (tab[height])
        height++;

    // Vérifier si la carte est vide
    if (height == 0)
        main_error("Map is empty");

    // Calculer la largeur de la carte (on suppose que toutes les lignes ont la même longueur)
    width = ft_strlen(tab[0]);

    // Créer une copie de la carte pour le flood fill
    char **map_copy = malloc(height * sizeof(char *));
    for (i = 0; i < height; i++)
    {
        map_copy[i] = ft_dup(tab[i]);
    }

    // Lancer le flood fill depuis la position du joueur
    printf("Lancement du flood fill depuis la position (%d, %d)\n", start_y, start_x);
    flood_fill(map_copy, start_y, start_x, height, width, '0', 'F');
    flood_fill(map_copy, start_y, start_x, height, width, 'N', 'F');
    flood_fill(map_copy, start_y, start_x, height, width, 'S', 'F');
    flood_fill(map_copy, start_y, start_x, height, width, 'E', 'F');
    flood_fill(map_copy, start_y, start_x, height, width, 'W', 'F');

    // Vérifier s'il reste des '0' non atteints, ou s'il y a accès aux espaces non valides
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (map_copy[i][j] == '0')
                main_error("Map has inaccessible areas");
        }
        free(map_copy[i]);
    }
    free(map_copy);
}