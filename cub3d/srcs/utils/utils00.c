/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils00.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:01:38 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/28 10:00:07 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!src || !dst)
		return (0);
	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

char	*ft_dup(char *src)
{
	char	*dup;
	int		len;

	len = ft_strlen(src);
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		main_error("Memory allocation failed");
	ft_strlcpy(dup, src, len + 1);
	return (dup);
}

int	split_count_word(char *str, char sep)
{
	unsigned int	i;
	unsigned int	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (str[i] != sep && str[i + 1] == sep)
		{
			nbr++;
			i++;
		}
		if (str[i] != sep && str[i + 1] == '\0')
		{
			nbr++;
			i++;
		}
		else
			i++;
	}
	return (nbr);
}

char	**split_create_tab(char *str, char sep, char **dest)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		j = i;
		while (str[i] && str[i] != sep)
			i++;
		if (i > j)
		{
			dest[k] = malloc(sizeof(char) * (i - j + 1));
			if (!dest[k])
				return (NULL);
			ft_strlcpy(dest[k++], &str[j], i - j + 1);
			dest[k] = NULL;
		}
	}
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		nbword;

	nbword = split_count_word((char *)s, c);
	dest = (char **)malloc(sizeof(char *) * (nbword + 1));
	if (!dest)
		return (NULL);
	dest = split_create_tab((char *)s, c, dest);
	dest[nbword] = (NULL);
	return (dest);
}
