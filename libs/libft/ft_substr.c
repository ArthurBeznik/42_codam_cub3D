/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:37:13 by edawood           #+#    #+#             */
/*   Updated: 2022/02/03 14:37:14 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len_from_start;

	if (!s)
		return (NULL);
	while (start && *s)
	{
		s++;
		start--;
	}
	s_len_from_start = ft_strlen(s);
	if (len > s_len_from_start)
		len = s_len_from_start;
	sub = ft_calloc(((int)len + 1), sizeof(char));
	if (!(sub) || sub == 0)
		return (0);
	ft_strlcpy(sub, s, len + 1);
	return (sub);
}
