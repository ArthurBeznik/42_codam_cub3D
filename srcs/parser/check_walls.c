#include <parser.h>

static void	st_find_player(t_file_data *file_data)
{
	int	x;
	int	y;

	y = 0;
	while (file_data->map_data->map[y])
	{
		x = 0;
		while (file_data->map_data->map[y][x])
		{
			if (is_player(file_data->map_data->map[y][x]))
			{
				file_data->player->x = x;
				file_data->player->y = y;
				file_data->player->facing = file_data->map_data->map[y][x];
				return ;
			}
			x++;
		}
		y++;
	}
}

// static char	**st_copy_map(t_map_data *map_data)
// {
// 	int		i;
// 	char	**copy;

// 	copy = (char **)malloc(sizeof(char *) * (map_data->rows_count + 1));
// 	// copy = NULL; // ? testing
// 	if (!copy)
// 		return (NULL);
// 	i = 0;
// 	while (map_data->map[i])
// 	{
// 		copy[i] = ft_strdup(map_data->map[i]);
// 		// copy[i] = NULL; // ? testing
// 		if (!copy[i])
// 		{
// 			free_2d(copy);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	copy[i] = NULL;
// 	return (copy);
// }

/**
 * ? <25 lines without testing comments
*/
bool	check_walls(t_file_data *file_data)
{
	bool	is_enclosed;
	int		player_x;
	int		player_y;

	// map_content = NULL; // ? testing
	if (!file_data->map_data)
		return (error_msg("Fetching map content"));
	file_data->map_data->rows_count = ft_count_rows((const char **)file_data->map_data->map);
	// rows = 0; // ? testing
	if (file_data->map_data->rows_count <= 0)
		return (error_msg("Getting nb of rows"));
	st_find_player(file_data);
	// printf("[x, y] = [%d, %d]\n", player_x, player_y); // ? testing
	// player_x = -1; // ? testing
	// player_y = -1; // ? testing
	player_x = file_data->player->x;
	player_y = file_data->player->y;
	if (player_x == ERROR || player_y == ERROR)
		return (error_msg("Finding player position"));
	is_enclosed = true;
	file_data->map_data->copy = copy_map(file_data->map_data->map, file_data->map_data->rows_count);
	// copy = NULL; // ? testing
	if (!file_data->map_data->copy)
		return (error_msg("Copying map"));
	flood_fill(player_y, player_x, file_data->map_data, &is_enclosed);
	// free_2d(file_data->map_data->copy);
	if (!is_enclosed)
		return (false);
	return (true);
	// system("leaks cub3D"); // ? testing
}
