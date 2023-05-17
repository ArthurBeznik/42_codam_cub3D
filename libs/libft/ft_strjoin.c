/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 14:36:11 by edawood       #+#    #+#                 */
/*   Updated: 2023/02/27 15:30:15 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *str1, char const *str2)
{
	size_t	str1len;
	size_t	str2len;
	char	*out;

	if (!str1 || !str2)
		return (0);
	str1len = ft_strlen(str1);
	str2len = ft_strlen(str2);
	out = ft_calloc((str1len + str2len + 1), sizeof(char));
	if (!out)
		return (0);
	ft_strlcpy(out, str1, str1len + 1);
	ft_strlcpy(out + str1len, str2, str2len + 1);
	free(str1);
	return (out);
}
