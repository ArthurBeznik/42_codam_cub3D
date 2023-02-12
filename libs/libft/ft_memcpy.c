/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:34:43 by edawood           #+#    #+#             */
/*   Updated: 2022/02/03 14:34:48 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*tmp_dst;
	const char	*tmp_src;

	if (dst == src)
		return (dst);
	tmp_dst = dst;
	tmp_src = src;
	while (n > 0)
	{
		n--;
		*tmp_dst = *tmp_src;
		tmp_dst++;
		tmp_src++;
	}
	return (dst);
}
