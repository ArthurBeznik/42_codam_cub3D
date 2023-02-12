/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/12 16:56:05 by abeznik       #+#    #+#                 */
/*   Updated: 2023/02/12 17:39:38 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	parser(int argc, char *argv[])
{
	if (argc != 2)
		return (EXIT_FAILURE);

	// ? to remove errors	
	if (!argv[1])
		return (EXIT_FAILURE);

	
	return (EXIT_SUCCESS);
}
