/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:05:10 by arthurbezni       #+#    #+#             */
/*   Updated: 2023/02/19 11:30:44 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	main(int argc, char *argv[])
{
	t_general_data data;
	t_file_data file_data;

	if (!parser(argc, argv, &file_data))
		// return (error_msg("Usage: ./cub3D <file_name>.cub"));
		return (logger(111, "main", "parser failure")); // ? example logger
	free(file_data.line);
	system("leaks cub3D");
	return (0);
}
