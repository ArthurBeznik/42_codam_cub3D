#include <cub3D.h>

void	terminate(t_graphics *graphics)
{
	mlx_close_window(graphics->mlx);
	mlx_terminate(graphics->mlx);
	exit(0);
}

void	free_close_window(t_graphics *graphics, void *var, char *str)
{
	ft_putendl_fd("Error\n", STDOUT_FILENO);
	ft_putendl_fd(str, STDOUT_FILENO);
	free(var);
	terminate(graphics);
}

bool	check_put_pixel(t_general_data *data, uint32_t x, uint32_t y)
{
	if (x > data->graphics.width || x < 0)
		return (error_msg("Invalid x"));
	if (y > data->graphics.height || y < 0)
		return (error_msg("Invalid y"));
	return (true);
}

bool	fill_map(t_general_data	*data)
{
	int		y;
	int		x;
	int		map_height;
	int		curr_line_len;

	data->file_data.map_data.copy = copy_map(data->file_data.map_data.map, \
		data->file_data.map_data.row);
	if (data->file_data.map_data.copy == NULL)
		return (false);
	map_height = data->file_data.map_data.row;
	y = 0;
	while (y < map_height)
	{
		curr_line_len = ft_strlen(data->file_data.map_data.copy[y]);
		x = 0;
		while (x < curr_line_len)
		{
			if (data->file_data.map_data.copy[y][x] == ' ')
				data->file_data.map_data.copy[y][x] = 'X';
			x++;
		}
		y++;
	}
	return (true);
}
