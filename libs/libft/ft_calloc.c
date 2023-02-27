/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 14:31:32 by edawood       #+#    #+#                 */
/*   Updated: 2023/02/27 15:39:00 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total;

	total = count * size;
	ptr = malloc(count * size);
	// ptr = NULL; // ? testing
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}
