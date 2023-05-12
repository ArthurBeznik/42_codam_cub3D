#include <parser.h>

static void	find_player(t_file_data *file_data)
{
	int	x;
	int	y;

	y = 0;
	while (file_data->map_data.map[y])
	{
		x = 0;
		while (file_data->map_data.map[y][x])
		{
			if (is_player(file_data->map_data.map[y][x]))
			{
				file_data->player.x = x;
				file_data->player.y = y;
				file_data->player.px = x;
				file_data->player.py = y;
				file_data->player.facing = file_data->map_data.map[y][x];
				return ;
			}
			x++;
		}
		y++;
	}
}

static bool	check_rows(t_file_data *file_data)
{
	file_data->map_data.row = \
		ft_count_rows((const char **)file_data->map_data.map);
	if (file_data->map_data.row <= 0)
		return (error_msg("Getting nb of rows"));
	return (true);
}

bool	check_walls(t_file_data *file_data)
{
	bool	is_enclosed;
	int		player_x;
	int		player_y;

	if (!check_rows(file_data))
		return (false);
	find_player(file_data);
	player_x = file_data->player.x;
	player_y = file_data->player.y;
	if (player_x == ERROR || player_y == ERROR)
		return (error_msg("Finding player position"));
	is_enclosed = true;
	file_data->map_data.copy = \
		copy_map(file_data->map_data.map, file_data->map_data.row);
	if (!file_data->map_data.copy)
		return (error_msg("Copying map"));
	flood_fill(player_y, player_x, &file_data->map_data, &is_enclosed);
	if (file_data->map_data.copy)
		free_2d(file_data->map_data.copy);
	if (!is_enclosed)
		return (false);
	return (true);
}
