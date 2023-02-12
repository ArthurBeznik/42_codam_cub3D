/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:37:07 by edawood           #+#    #+#             */
/*   Updated: 2022/02/03 14:37:08 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_in_str(char s1, char const *set)
{
	while (*set)
	{
		if (s1 == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char						*trim;
	const char					*s2;

	if (!s1)
		return (NULL);
	while (*s1 && set_in_str(*s1, set))
		s1++;
	s2 = s1;
	while (*s1)
		s1++;
	s1--;
	while (set_in_str(*s1, set) && s1 >= s2)
		s1--;
	trim = ft_calloc((s1 - s2 + 2), sizeof(char));
	if (!(trim))
		return (NULL);
	ft_strlcpy(trim, s2, (s1 - s2) + 2);
	return (trim);
}
