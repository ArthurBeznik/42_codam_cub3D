/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arthurbeznik <arthurbeznik@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/12 15:05:10 by arthurbezni   #+#    #+#                 */
/*   Updated: 2023/02/14 14:06:29 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char *argv[])
{
	if (!parser(argc, argv))
		// return (error_msg("Usage: ./cub3D <file_name>.cub"));
		return (logger(111, "main", "parser failure")); // ? example logger
	return (0);
}
