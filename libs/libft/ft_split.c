/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:35:23 by edawood           #+#    #+#             */
/*   Updated: 2022/02/03 14:35:31 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**clear_arr(char **arr)
{
	while (arr && *arr)
	{
		free(*arr);
		arr++;
	}
	free(arr);
	return (0);
}

static void	*ft_arrlcpy(void *dst_arr, void *src_arr, size_t arr_len)
{
	long	*temp_dst_arr;
	long	*temp_src_arr;

	temp_dst_arr = dst_arr;
	temp_src_arr = src_arr;
	while (arr_len > 0)
	{
		arr_len--;
		*temp_dst_arr = *temp_src_arr;
		temp_dst_arr++;
		temp_src_arr++;
	}
	return (dst_arr);
}

static int	len(char **arr, char const *s, char c)
{
	char		**temp_arr;
	const char	*temp_char;

	if (arr != 0)
	{
		temp_arr = arr;
		while (*temp_arr)
			temp_arr++;
		return ((int)(temp_arr - arr));
	}
	else
	{
		temp_char = s;
		while (*temp_char && *temp_char != c)
			temp_char++;
		return ((int)(temp_char - s));
	}
}

static char	**add_arr(char **arr, char *s)
{
	char	**new_arr;
	int		arr_len;

	arr_len = 0;
	if (arr == 0)
		new_arr = ft_calloc(2, sizeof(char *));
	else
	{
		arr_len = len(arr, 0, 0);
		new_arr = ft_calloc(arr_len + 2, sizeof(char *));
		if (new_arr == 0)
			return (clear_arr(arr));
		ft_arrlcpy(new_arr, arr, arr_len);
		free(arr);
	}
	*(new_arr + arr_len) = s;
	return (new_arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	char	*temp;

	arr = 0;
	if (!s)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == 0)
			break ;
		temp = ft_calloc((len(0, s, c) + 1), sizeof(char));
		if (!temp)
			return (NULL);
		ft_memcpy(temp, (void *)s, len(0, s, c));
		arr = add_arr(arr, temp);
		while (*s && (*s != c))
			s++;
	}
	if (arr == 0)
		return (ft_calloc(1, sizeof(char *)));
	return (arr);
}
