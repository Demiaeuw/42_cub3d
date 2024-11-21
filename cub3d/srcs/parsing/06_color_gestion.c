/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_color_gestion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:09:43 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/21 05:25:55 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * Convertit des valeurs RGB (rouge, vert, bleu) en une couleur hexadécimale.
 * Les composantes sont combinées en une seule valeur de type entier.
 * 
 * param r - Composante rouge (0-255).
 * param g - Composante verte (0-255).
 * param b - Composante bleue (0-255).
 * return Une couleur hexadécimale au format 0xRRGGBB.
 */
int	convert_rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

/**
 * Supprime les caractères d'espacement en fin de chaîne, y compris
 * les espaces (`' '`), les tabulations (`'\t'`), et les sauts de ligne (`'\n'`)
 * Modifie directement la chaîne passée en paramètre.
 */
void	trim_trailing_whitespace(char *str)
{
	int	len;

	len = strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n'
			|| str[len - 1] == '\t'))
	{
		str[len - 1] = '\0';
		len--;
	}
}

/**
 * Valide et analyse une chaîne de caractères représentant
 * une couleur au format "R,G,B".
 * Chaque composante (R, G, B) doit être un entier entre 0 et 255.
 * En cas de format invalide ou de valeur hors plage, retourne -1.
 * Si la validation réussit, convertit la couleur en une valeur hexadécimale
 * au format 0xRRGGBB à l'aide de `convert_rgb_to_hex`.
 * 
 * param color_str - Chaîne représentant la couleur au format "R,G,B".
 * return Une couleur hexadécimale au format 0xRRGGBB ou -1 en cas d'erreur.
 */
int	validate_and_parse_color(char *color_str)
{
	int		r;
	int		g;
	int		b;
	char	*endptr;

	trim_trailing_whitespace(color_str);
	r = ft_strtol(color_str, &endptr, 10);
	if (*endptr != ',' || r < 0 || r > 255)
		return (-1);
	color_str = endptr + 1;
	g = ft_strtol(color_str, &endptr, 10);
	if (*endptr != ',' || g < 0 || g > 255)
		return (-1);
	color_str = endptr + 1;
	b = ft_strtol(color_str, &endptr, 10);
	if (*endptr != '\0' || b < 0 || b > 255)
		return (-1);
	return (convert_rgb_to_hex(r, g, b));
}

/**
 * Vérifie et analyse une ligne pour définir une couleur (plafond ou sol).
 * Si la ligne commence par le type attendu (par exemple, "F " ou "C ") et que 
 * la couleur n'est pas encore définie (is_set == 0), elle valide et convertit
 * la chaîne en une valeur hexadécimale. En cas de format invalide, affiche un
 * message d'erreur et quitte le programme.
 *
 * Paramètres :
 * - line : La ligne à analyser.
 * - color : Pointeur vers l'entier où la couleur convertie sera stockée.
 * - is_set : Indicateur si la couleur a déjà été définie.
 * - type : Le type attendu ("F " pour le sol, "C " pour le plafond).
 */
void	check_set_color(char *line, int *color, int *is_set, char *type)
{
	if (ft_strncmp(line, type, 2) == 0 && !*is_set)
	{
		*color = validate_and_parse_color(line + 2);
		if (*color == -1)
			message_error("Invalid color format", NULL);
		*is_set = 1;
	}
}

/**
 * Gère l'extraction et la validation des couleurs pour le sol et le plafond
 * à partir du fichier de configuration. 
 * 
 * Parcourt chaque ligne du fichier, vérifie si elle 
 * correspond aux types "F " (sol)
 * ou "C " (plafond), et utilise `check_set_color` pour 
 * valider et convertir les valeurs.
 * Si une couleur manque ou si le fichier est inaccessible, 
 * affiche un message 
 * d'erreur et quitte le programme.
 */
void	color_gestion(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	int		floor_set;
	int		ceiling_set;

	floor_set = 0;
	ceiling_set = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		message_error("Failed to open file", game);
	line = get_next_line(fd);
	while (line != NULL)
	{
		check_set_color(line, &game->map->color_floor, &floor_set, "F ");
		check_set_color(line, &game->map->color_ceiling, &ceiling_set, "C ");
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!floor_set || !ceiling_set)
		message_error("Missing floor or ceiling color in file", game);
}
