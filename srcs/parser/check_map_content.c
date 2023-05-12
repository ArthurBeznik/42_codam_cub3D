#include <parser.h>

static bool	check_valid_char(const char c)
{
	if (c != ' ' && c != '1' && c != '0'
		&& c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (false);
	return (true);
}

bool	check_map_content(const char **map)
{
	int	x;
	int	y;
	int	player_count;

	if (!map)
		return (error_msg("Fetching map content"));
	y = 0;
	player_count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!check_valid_char(map[y][x]))
				return (error_msg("Invalid character found in map"));
			if (is_player(map[y][x]))
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (error_msg("There's more or less than one player in the map"));
	return (true);
}
