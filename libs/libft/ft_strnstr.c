/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:36:52 by edawood           #+#    #+#             */
/*   Updated: 2022/02/03 14:36:53 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_len;

	n_len = ft_strlen(needle);
	if (*needle == 0)
		return ((char *)haystack);
	if (len == 0)
		return (0);
	while (*haystack)
	{
		if (!ft_strncmp(haystack, needle, n_len))
			return ((char *)haystack);
		haystack++;
		len--;
		if (len < n_len)
			break ;
	}
	return (0);
}
