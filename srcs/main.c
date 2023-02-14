/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arthurbeznik <arthurbeznik@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/12 15:05:10 by arthurbezni   #+#    #+#                 */
/*   Updated: 2023/02/14 12:37:35 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char *argv[])
{
	if (!parser(argc, argv))
		return (exit_error("Usage: ./cub3D <map>.cub"));
	// if (run_game(...))
	// 	return (1);

	return (0);
}
