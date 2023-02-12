/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:33:26 by edawood           #+#    #+#             */
/*   Updated: 2022/10/12 16:49:09 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recursive(int num, char *str, int counter)
{
	while (*str)
		str++;
	while (*str == '\0' && counter > 0)
	{
		if (num < 10)
		{
			*str = (num + '0');
			str++;
			counter--;
			return ;
		}
		else
			ft_recursive(num / 10, str, counter);
		ft_recursive(num % 10, str, counter);
	}
}

static char	*ft_minslcpy(char *dst, const char *src, size_t dstsize)
{
	char				*temp_dst;
	const char			*temp_src;

	temp_dst = dst;
	temp_src = src;
	while (dstsize > 0 && *temp_src)
	{
		dstsize--;
		*temp_dst = *temp_src;
		temp_dst++;
		temp_src++;
	}
	return (dst);
}

static int	ft_counter(int num, int counter)
{
	if (num < 0)
	{
		num = -num;
		counter++;
	}
	while (num > 0)
	{
		num = num / 10;
		counter++;
	}
	return (counter);
}

static char	*ft_negative(int num, char *str)
{
	if (num == 0)
	{
		str = ft_calloc(2, sizeof(char));
		if (!str)
			return (NULL);
		str = ft_minslcpy(str, "0", 1);
	}
	if (num == -2147483648)
	{
		str = ft_calloc(12, sizeof(char));
		if (!str)
			return (NULL);
		str = ft_minslcpy(str, "-2147483648", 12);
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		negative;
	int		counter;

	str = NULL;
	counter = 0;
	negative = 1;
	counter = ft_counter(n, counter);
	if (n < 0)
	{
		n = -n;
		negative = -1;
	}
	if (n <= 0)
		return (str = ft_negative(n, str));
	str = ft_calloc(counter + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (negative == -1)
		*str = '-';
	ft_recursive(n, str, counter);
	return (str);
}
