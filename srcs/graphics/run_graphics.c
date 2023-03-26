#include <graphics.h>

bool	fill_map(t_general_data	*data)
{
	int		y;
	int		x;
	int		map_height;
	int		curr_line_len;

	data->file_data->map_data->copy = copy_map(data->file_data->map_data->map, data->file_data->map_data->row);
	if (data->file_data->map_data->copy == NULL)
		return (false);
	map_height = data->file_data->map_data->row;
	y = 0;
	while (y < map_height)
	{
		curr_line_len = ft_strlen(data->file_data->map_data->copy[y]);
		x = 0;
		while (x < curr_line_len)
		{
			if (data->file_data->map_data->copy[y][x] == ' ')
				data->file_data->map_data->copy[y][x] = 'X';
			x++;
		}
		y++;
	}
	return (true);
}

bool	run_graphics(t_general_data	*data)
{
	t_graphics graphics;

	data->graphics = &graphics;
	if (!init_graphics(data, data->graphics))
		return (error_msg("init_graphics"));

	if (!fill_map(data))
		return (error_msg("Filling map"));

	data->graphics->init_dir = false;
	if (!draw_2d_map(data, data->graphics->img))
		return (error_msg("Drawing 2D map"));

	if ((mlx_image_to_window(data->graphics->mlx, data->graphics->img, 0, 0) < 0))
		return (error_msg("mlx_image_to_window"));

	mlx_loop_hook(data->graphics->mlx, &captain, data);

	mlx_loop(data->graphics->mlx);

	mlx_terminate(data->graphics->mlx);
	return (true);
}
