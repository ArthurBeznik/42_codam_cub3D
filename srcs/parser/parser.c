/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/12 16:56:05 by abeznik       #+#    #+#                 */
/*   Updated: 2023/02/19 14:34:49 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	init_map_file_data(t_file_data *file_data)
{
	file_data->map_extention = ".cub";
	file_data->buflen = 1;
	file_data->fd = 0;
}

bool	parser(int argc, char *argv[], t_file_data *file_data)
{
	init_map_file_data(file_data);
	if (argc != 2)
		return (error_msg("Usage: ./cub3D <file_name>.cub"));
	if (!check_ext(argv[1], file_data))
		return (false);
	if (!check_map(argv[1], file_data))
		return (false);
	return (true);
}
