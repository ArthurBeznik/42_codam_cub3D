/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:36:19 by edawood           #+#    #+#             */
/*   Updated: 2022/02/03 14:36:20 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	size;

	size = ft_strlen(dst);
	if (dstsize < size)
		return (dstsize + ft_strlen(src));
	else
		ft_strlcpy(dst + size, src, dstsize - size);
	return (size + ft_strlen(src));
}
