#include <parser.h>

static bool	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

static void	find_player(t_map_data *map_data)
{
	int	x;
	int	y;

	y = 0;
	while (map_data->map[y])
	{
		x = 0;
		while (map_data->map[y][x])
		{
			if (is_player(map_data->map[y][x]))
			{
				map_data->player->x = x;
				map_data->player->y = y;
				map_data->player->facing = map_data->map[y][x];
				return ;
			}
			x++;
		}
		y++;
	}
}

static char	**copy_map(t_map_data *map_data)
{
	int		i;
	char	**copy;

	copy = (char **)malloc(sizeof(char *) * (map_data->rows_count + 1));
	// copy = NULL; // ? testing
	if (!copy)
		return (NULL);
	i = 0;
	while (map_data->map[i])
	{
		copy[i] = ft_strdup(map_data->map[i]);
		// copy[i] = NULL; // ? testing
		if (!copy[i])
		{
			free_2d(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

/**
 * ? <25 lines without testing comments
*/
bool	check_walls(t_map_data *map_data)
{
	bool	is_enclosed;
	int		player_x;
	int		player_y;

	// map_content = NULL; // ? testing
	if (!map_data)
		return (error_msg("Fetching map content"));
	map_data->rows_count = ft_count_rows((const char **)map_data->map);
	// rows = 0; // ? testing
	if (map_data->rows_count <= 0)
		return (error_msg("Getting nb of rows"));
	find_player(map_data);
	// printf("[x, y] = [%d, %d]\n", player_x, player_y); // ? testing
	// player_x = -1; // ? testing
	// player_y = -1; // ? testing
	player_x = map_data->player->x;
	player_y = map_data->player->y;
	if (player_x == ERROR || player_y == ERROR)
		return (error_msg("Finding player position"));
	is_enclosed = true;
	map_data->copy = copy_map(map_data);
	// copy = NULL; // ? testing
	if (!map_data->copy)
		return (error_msg("Copying map"));
	flood_fill(player_y, player_x, map_data, &is_enclosed);
	free_2d(map_data->copy);
	if (!is_enclosed)
		return (false);
	return (true);
	// system("leaks cub3D"); // ? testing
}
