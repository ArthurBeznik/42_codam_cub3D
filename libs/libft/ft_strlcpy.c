/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:36:26 by edawood           #+#    #+#             */
/*   Updated: 2022/02/03 14:36:27 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char		*temp_dst;
	const char	*temp_src;

	if (dstsize == 0)
		return (ft_strlen(src));
	temp_dst = dst;
	temp_src = src;
	while (dstsize > 0 && *temp_src)
	{
		dstsize--;
		*temp_dst = *temp_src;
		temp_dst++;
		temp_src++;
	}
	if (dstsize == 0)
		*(temp_dst - 1) = 0;
	else
		*temp_dst = 0;
	return (ft_strlen(src));
}
