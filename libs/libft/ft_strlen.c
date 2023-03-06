/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 14:36:33 by edawood       #+#    #+#                 */
/*   Updated: 2023/03/03 14:14:15 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != 0)
	{
		i++;
	}
	return (i);
}
