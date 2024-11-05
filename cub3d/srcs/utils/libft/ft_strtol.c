/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:11:46 by acabarba          #+#    #+#             */
/*   Updated: 2024/11/05 16:31:43 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_overflow(long result, int digit, int sign)
{
	if (sign == 1 && result > (LONG_MAX - digit) / 10)
		return (1);
	if (sign == -1 && - result < (LONG_MIN + digit) / 10)
		return (1);
	return (0);
}

static long	ft_process_result(const char *str, int sign, char **endptr)
{
	long	result;
	int		digit;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (ft_is_overflow(result, digit, sign))
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		result = result * 10 + digit;
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	int	sign;

	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (base != 10)
		return (0);
	return (ft_process_result(str, sign, endptr));
}
