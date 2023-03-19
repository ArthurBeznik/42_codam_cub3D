#include <parser.h>

static bool	st_check_valid_char(const char c)
{
	// return (false); // ? testing
	if (c != ' ' && c != '1' && c != '0'
		&& c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (false);
	return (true);
}

/**
 * ? <25 lines without testing comments
*/
bool	check_map_content(const char **map)
{
	int	x;
	int	y;
	int	player_count;

	// map = NULL; // ? testing
	if (!map)
		return (error_msg("Fetching map content"));
	y = 0;
	player_count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!st_check_valid_char(map[y][x]))
				return (error_msg("Invalid character found in map"));
			if (is_player(map[y][x]))
				player_count++;
			x++;
		}
		y++;
	}
	// player_count = 4; // ? testing
	if (player_count != 1)
		return (error_msg("Only one starting position allowed"));
	return (true);
}
