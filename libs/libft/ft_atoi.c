/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 14:31:10 by edawood       #+#    #+#                 */
/*   Updated: 2023/02/27 13:01:30 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

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
		return (-1);
	result = (*str - '0') * -1;
	str++;
	while (ft_isdigit(*str))
	{
		result *= 10;
		result -= (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (result);
}

int	ft_atoi(const char *str)
{
	int	min;
	int	result;

	min = -1;
	while (whitespace_checker(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			min = 1;
		str++;
	}
	result = int_converter(str);
	if (result == -1)
		return(-1);
	else
		return (int_converter(str) * min);
}
