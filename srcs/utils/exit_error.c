/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/12 17:26:06 by abeznik       #+#    #+#                 */
/*   Updated: 2023/02/13 18:14:00 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

/**
 * Examples:
 * 	exit_error(3, "main", "malloc failure");
 * 		should output to standard error:
 * 			"main: malloc failure" 
 * 		or 
 * 	exit_error(errno, "main", NULL);
 * 		should output to standard error:
 * 			main: <errno message>
 * 	both functions exit with given exit code after displaying error message
*/
static void	st_write_msg(const char *fn, const char *msg)
{
	ft_putstr_fd("Error", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	if (fn)
	{
		ft_putstr_fd(fn, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

/**
 * Exits program on error, and optionally displays an error message.
 * @param code 		Error code to exit with.
 * @param function	(optional) Function where the error was encountered.
 * @param message	(optional) Custom error message to display.
*/
int	logger(const int code, const char *function, const char *message)
{
	if (function || message)
		st_write_msg(function, message);
	return (code);
}

int	exit_error(const char *message)
{
	if (message)
		st_write_msg(NULL, message);
	return (EXIT_FAILURE);
}