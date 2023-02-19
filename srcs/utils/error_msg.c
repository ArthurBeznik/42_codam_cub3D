/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_msg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/14 13:52:51 by abeznik       #+#    #+#                 */
/*   Updated: 2023/02/19 14:22:33 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

/**
 * ? This is to comply with the subject when parsing the scene file.
*/
bool	error_msg(const char *message)
{
	ft_putstr_fd("Error", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	ft_putchar_fd('\t', STDERR_FILENO);
	if (message)
	{
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	return (false);
}
