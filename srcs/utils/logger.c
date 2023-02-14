/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logger.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/14 13:54:14 by abeznik       #+#    #+#                 */
/*   Updated: 2023/02/14 14:05:53 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * Examples:
 * 	logger(3, "main", "malloc failure");
 * 		should output to standard error:
 * 			"main: malloc failure" 
 * 		or 
 * 	logger(errno, "main", NULL);
 * 		should output to standard error:
 * 			main: <errno message>
 * 	both functions exit with given exit code after displaying error message
*/
static void	st_write_log(const char *fn, const char *msg)
{
	ft_putstr_fd("Error", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	ft_putchar_fd('\t', STDERR_FILENO);
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
 * ? This is for us to use in "debugging", so we'll probably remove it at some
 * ? point but it's useful to have now I think.
*/
int	logger(const int code, const char *function, const char *message)
{
	if (function || message)
		st_write_log(function, message);
	exit(code);
}
