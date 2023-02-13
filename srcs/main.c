/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arthurbeznik <arthurbeznik@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/12 15:05:10 by arthurbezni   #+#    #+#                 */
/*   Updated: 2023/02/13 18:13:49 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int argc, char *argv[])
{
	if (!parser(argc, argv))
		return (exit_error("Usage: ./cub3D <map>.cub"));
	// if (run_game(...))
	// 	return (1);

	return (0);
}
