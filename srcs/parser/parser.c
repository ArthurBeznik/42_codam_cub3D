/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/12 16:56:05 by abeznik       #+#    #+#                 */
/*   Updated: 2023/02/14 12:37:25 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	parser(int argc, char *argv[])
{
	if (argc != 2)
		return (false);

	// ? to remove errors	
	if (!argv[1])
		return (false);

	return (true);
}
