
#include <parser.h>

int get_nb_rows(char **map)
{
	int y;

	y = 0;
	while (map[y])
		y++;
	return (y);
}

bool is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

int find_player(char **map, int xy)
{
	int x;
	int y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player(map[y][x]))
			{
				if (xy == Y)
					return (xy = y);
				if (xy == X)
					return (xy = x);
			}
			x++;
		}
		y++;
	}
	return (-1);
}

bool check_walls(char **map_content)
{
	int rows;
	int player_x;
	int player_y;
	bool is_enclosed;

	if (!map_content)
		return (false);
	rows = get_nb_rows(map_content);
	// rows = 0; // ? testing
	if (rows <= 0)
		return (error_msg("Getting nb of rows"));
	player_x = find_player(map_content, X);
	player_y = find_player(map_content, Y);
	// printf("[x, y] = [%d, %d]\n", player_x, player_y); // ? testing
	// player_x = -1; // ? testing
	// player_y = -1; // ? testing
	if (player_x == -1 || player_y == -1)
		return (error_msg("Finding player position"));
	is_enclosed = true;
	flood_fill(player_y, player_x, map_content, &is_enclosed, rows);
	if (!is_enclosed)
		return (false);
	return (true);
}
