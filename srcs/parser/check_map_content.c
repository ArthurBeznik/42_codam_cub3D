
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

bool	check_map_content(char **map_content)
{
	int	x;
	int	y;
	int	player_count;

	// map_content = NULL; // ? testing
	if (!map_content)
		return (error_msg("Fetching map content"));
	y = 0;
	player_count = 0;
	while (map_content[y])
	{
		x = 0;
		while (map_content[y][x])
		{
			if (!check_valid_char(map_content[y][x]))
				return (error_msg("Invalid character found in map"));
			if (is_player(map_content[y][x]))
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
