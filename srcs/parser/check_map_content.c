
#include <parser.h>

static bool	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

static bool	check_valid_char(char c)
{
	// return (false); // ? testing
	if (c != ' ' && c != '1' && c != '0'
		&& c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (false);
	return (true);
}

/**
 * TODO fix too many lines
*/
bool	check_map_content(char **map)
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
			if (!check_valid_char(map[y][x]))
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
