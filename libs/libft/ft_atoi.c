/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:31:10 by edawood           #+#    #+#             */
/*   Updated: 2022/10/12 16:48:42 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	whitespace_checker(char c)
{
	return (c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r'
		|| c == ' ');
}

static int	int_converter(const char *str)
{
	int	result;

	if (!ft_isdigit(*str))
		return (0);
	result = (*str - '0') * -1;
	str++;
	while (ft_isdigit(*str))
	{
		result *= 10;
		result -= (*str - '0');
		str++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int	min;

	min = -1;
	while (whitespace_checker(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			min = 1;
		str++;
	}
	return (int_converter(str) * min);
}
