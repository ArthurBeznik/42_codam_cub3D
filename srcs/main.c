/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:05:10 by arthurbezni       #+#    #+#             */
/*   Updated: 2023/02/15 12:07:15 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int argc, char *argv[])
{
	if (!parser(argc, argv))
		// return (error_msg("Usage: ./cub3D <file_name>.cub"));
		return (logger(111, "main", "parser failure")); // ? example logger
	return (0);
}
