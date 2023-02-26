
#include <parser.h>
#include <stdio.h>

void	print_map(char **map)
{
	int x;
	int y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			printf("%c ", map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n");
}

// void	flood_fill(int y, int x, char **map)
// {
// 	// print_map(map);
// 	if (map[y][x] == '1')
// 		return ;
// 	map[y][x] = '1';
// 	flood_fill(y, (x + 1), map);
// 	flood_fill(y, (x - 1), map);
// 	flood_fill((y + 1), x, map);
// 	flood_fill((y - 1), x, map);
// }

bool	check_map(char *file_name, t_file_data *file_data)
{
	file_data->fd = open(file_name, O_RDONLY);
	if (file_data->fd == ERROR)
		return (error_msg("Opening scene file"));
	file_data->line = read_file(file_data);
	if (!file_data->line)
		return (error_msg("Reading scene file"));
	if (!read_scene_file(file_data))
		return (error_msg("Parsing scene file data"));
	// if (!check_identifiers(file_data->identifiers, ".png"))
	// 	return (error_msg("Invalid identifiers"));
	// if (!check_map_content(file_data->map_content))
	// 	return (error_msg("Invalid content in map"));
	print_map(file_data->map_content);
	if (!check_walls(file_data->map_content))
		return (error_msg("Surrounding walls required"));
	print_map(file_data->map_content);
	return (true);
}
