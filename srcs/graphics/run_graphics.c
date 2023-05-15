#include <cub3D.h>

static bool	fill_map(t_general_data	*data)
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

static bool	init_graphic_structs(t_general_data *data)
{
	if (!init_graphics(data))
		return (error_msg("init_graphics"));
	if (!init_textures(data))
		return (error_msg("init_textures"));
	init_dda(data);
	if (!init_calc(data))
		return (error_msg("init_calc"));
	return (true);
}

bool	run_graphics(t_general_data *data)
{
	if (!init_graphic_structs(data))
		return (error_msg("init_graphics"));
	if (!fill_map(data))
		return (error_msg("Filling map"));
	if ((mlx_image_to_window(data->graphics.mlx, \
		data->graphics.img_3d, 0, 0) < 0))
		return (error_msg("mlx_image_to_window 3D"));
	mlx_loop_hook(data->graphics.mlx, &captain, data);
	mlx_loop(data->graphics.mlx);
	mlx_terminate(data->graphics.mlx);
	return (true);
}
