#include <cub3D.h>

static void	init_west_east(t_general_data *data)
{
	if (data->file_data.player.facing == 'W')
	{
		data->graphics.dda.dir_x = -1;
		data->graphics.dda.dir_y = 0;
		data->graphics.dda.plane_x = 0;
		data->graphics.dda.plane_y = -0.66;
	}
	else if (data->file_data.player.facing == 'E')
	{
		data->graphics.dda.dir_x = 1;
		data->graphics.dda.dir_y = 0;
		data->graphics.dda.plane_x = 0;
		data->graphics.dda.plane_y = 0.66;
	}
}

static void	init_north_south(t_general_data *data)
{
	if (data->file_data.player.facing == 'N')
	{
		data->graphics.dda.dir_x = 0;
		data->graphics.dda.dir_y = -1;
		data->graphics.dda.plane_x = 0.66;
		data->graphics.dda.plane_y = 0;
	}
	else if (data->file_data.player.facing == 'S')
	{
		data->graphics.dda.dir_x = 0;
		data->graphics.dda.dir_y = 1;
		data->graphics.dda.plane_x = -0.66;
		data->graphics.dda.plane_y = 0;
	}
}

void	init_dir_plane(t_general_data *data)
{
	if (data->file_data.player.facing == 'N' || \
		data->file_data.player.facing == 'S')
		init_north_south(data);
	else if (data->file_data.player.facing == 'W' || \
		data->file_data.player.facing == 'E')
		init_west_east(data);
}

bool	fill_dda_data(t_general_data *data)
{
	init_dir_plane(data);
	data->graphics.dda.w = data->graphics.width;
	data->graphics.dda.h = data->graphics.height;
	data->graphics.dda.pos_x = data->file_data.player.x + 0.5;
	data->graphics.dda.pos_y = data->file_data.player.y + 0.5;
	return (true);
}

bool	run_graphics(t_general_data *data)
{
	if (!init_graphics(data))
		return (error_msg("init_graphics"));
	if (!init_textures(data))
		return (error_msg("init_textures"));
	if (!init_dda(data))
		return (error_msg("init_dda"));
	if (!init_calc(data))
		return (error_msg("init_calc"));
	if (!fill_map(data))
		return (error_msg("Filling map"));
	if (!fill_dda_data(data))
		return (error_msg("Filling dda data"));
	data->graphics.init_dir = false;
	if (!draw_2d_map(data))
		return (error_msg("Drawing 2D map"));
	if ((mlx_image_to_window(data->graphics.mlx, \
		data->graphics.img_3d, 0, 0) < 0))
		return (error_msg("mlx_image_to_window 3D"));
	if ((mlx_image_to_window(data->graphics.mlx, data->graphics.img, 0, \
		data->graphics.height - data->graphics.height / 2.25) < 0))
		return (error_msg("mlx_image_to_window 2D"));
	mlx_loop_hook(data->graphics.mlx, &captain, data);
	mlx_loop(data->graphics.mlx);
	mlx_terminate(data->graphics.mlx);
	return (true);
}
