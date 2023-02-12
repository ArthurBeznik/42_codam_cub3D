/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:36:45 by edawood           #+#    #+#             */
/*   Updated: 2022/02/03 14:36:46 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*temps1;
	const unsigned char	*temps2;

	temps1 = (const unsigned char *)s1;
	temps2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while (*temps1 == *temps2 && *temps1 && *temps2 && n > 1)
	{
		temps1++;
		temps2++;
		n--;
	}
	return (*temps1 - *temps2);
}
