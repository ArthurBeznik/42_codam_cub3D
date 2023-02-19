/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/19 10:54:21 by edawood       #+#    #+#                 */
/*   Updated: 2023/02/19 14:23:01 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

bool	check_walls(t_map *map_data)
{
	int x;
	int y;

	y = 0;
	while (y < map_data->y_size)
	{
		x = 0;
		while (x < map_data->x_size)
		{
			if (y == 0 && map_data->map[y][x] != '1') // first line
				return (false);
			else if (y == map_data->y_size - 1 && map_data->map[y][x] != '1') // last line
				return (false);
			else if (map_data->map[y][0] != '1' && map_data->map[y][map->x_size - 1] != '1') // other lines
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	check_map(char *file_name, t_file_data *file_data)
{
	file_data->fd = open(file_name, O_RDONLY);
	if (file_data->fd == ERROR)
		return (logger(EXIT_FAILURE, "check_map", "Error opening file"), false);
	file_data->line = read_file(file_data);
	if (!file_data->line)
		return (logger(EXIT_FAILURE, "check_map", "Error reading scene file"), false);
	if (!check_walls(file_data->map_data))
		return (error_msg("Surrounding walls"));
	return (true);
}