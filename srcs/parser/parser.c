/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/12 16:56:05 by abeznik       #+#    #+#                 */
/*   Updated: 2023/02/19 14:23:19 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	init_map_file_data(t_file_data *file_data)
{
	file_data->map_extention = ".cub";
	file_data->buflen = 1;
	file_data->fd = 0;

	t_map *map_data = (t_map *)malloc(sizeof(t_map));

	char **map = (char **)malloc(sizeof(char *) * 1024);
	map[0] = "111";
	map[1] = "101";
	map[2] = "111";

	map_data->x_size = 3;
	map_data->y_size = 3;
	map_data->map = map;
	file_data->map_data = map_data;
}

bool	parser(int argc, char *argv[], t_file_data *file_data)
{
	init_map_file_data(file_data);
	if (argc != 2)
		return (false);
	if (!check_ext(argv[1], file_data))
		return (false);
	if (!check_map(argv[1], file_data))
		return (false);
	return (true);
}
