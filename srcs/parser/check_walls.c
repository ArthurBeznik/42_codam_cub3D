
#include <parser.h>

static int	get_nb_rows(char **map)
{
	int	y;

	y = 0;
	while (map[y])
		y++;
	return (y);
}

static bool	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

static int	find_player(char **map, int xy)
{
	int	x;
	int	y;

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

char	**copy_map(char **map, int rows)
{
	int		i;
	char	**copy;

	copy = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

bool	check_walls(char **map_content)
{
	int		rows;
	int		player_x;
	int		player_y;
	bool	is_enclosed;
	char	**copy;

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
	copy = copy_map(map_content, rows);
	if (!copy)
		return (error_msg("Copying map"));
	flood_fill(player_y, player_x, copy, &is_enclosed, rows);
	free_2d(copy);
	if (!is_enclosed)
		return (false);
	return (true);
	// system("leaks cub3D"); // ? testing
}
