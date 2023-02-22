
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
	int y;

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
