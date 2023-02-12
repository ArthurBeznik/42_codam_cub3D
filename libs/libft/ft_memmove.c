/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:34:50 by edawood           #+#    #+#             */
/*   Updated: 2022/02/03 14:34:55 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	backwards(char *dst, const char *src, size_t len)
{
	while (len > 0)
	{
		len--;
		*dst = *src;
		dst--;
		src--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*pdst;
	const char		*psrc;

	pdst = dst;
	psrc = src;
	if (dst == src)
		return (dst);
	if (pdst < psrc)
	{
		while ((int)len > 0)
		{
			*pdst = *psrc;
			pdst++;
			psrc++;
			len--;
		}
	}
	else
	{
		pdst += (len - 1);
		psrc += (len - 1);
		backwards(pdst, psrc, len);
	}
	return (dst);
}
