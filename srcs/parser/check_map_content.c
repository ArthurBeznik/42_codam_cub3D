
#include <parser.h>

static bool check_valid_char(char c)
{
	if (c != ' ' && c != '1' && c != '0'
		&& c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (false);
	return (true);
}

bool	check_map_content(char **map_content)
{
	int x;
	int x_size;
	int y;
	int y_size;

	if (!map_content)
		return (false);
	y = 0;
	while (map_content[y])
	{
		x = 0;
		while (map_content[y][x])
		{
			if (!check_valid_char(map_content[y][x]))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

/**
 * TODO add these lines in check_map.c after check_identifiers
 */
// if (!check_map_content(file_data->map_content))
// 	return (error_msg("Invalid content in map"));

/**
 * TODO add this line in parser.h
 */
// bool	check_map_content(char **map_content);
