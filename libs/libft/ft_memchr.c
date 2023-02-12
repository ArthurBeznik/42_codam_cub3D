/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:34:28 by edawood           #+#    #+#             */
/*   Updated: 2022/02/03 14:34:34 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		ch;

	str = (const unsigned char *)s;
	ch = c;
	while (n)
	{
		if (*str == ch)
			return ((void *) str);
		str++;
		n--;
	}
	if (ch == 0 && *str == ch)
		return (NULL);
	return (0);
}
