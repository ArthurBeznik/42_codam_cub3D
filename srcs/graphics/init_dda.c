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

static void	init_dir_plane(t_general_data *data)
{
	if (data->file_data.player.facing == 'N' || \
		data->file_data.player.facing == 'S')
		init_north_south(data);
	else if (data->file_data.player.facing == 'W' || \
		data->file_data.player.facing == 'E')
		init_west_east(data);
}

static void	fill_dda_data(t_general_data *data)
{
	init_dir_plane(data);
	data->graphics.dda.pos_x = data->file_data.player.x + 0.5;
	data->graphics.dda.pos_y = data->file_data.player.y + 0.5;
}

void	init_dda(t_general_data *data)
{
	data->graphics.dda.camera_x = NA;
	data->graphics.dda.delta_dist_x = NA;
	data->graphics.dda.delta_dist_y = NA;
	data->graphics.dda.dir_x = NA;
	data->graphics.dda.dir_y = NA;
	data->graphics.dda.hit = NA;
	data->graphics.dda.map_x = NA;
	data->graphics.dda.map_y = NA;
	data->graphics.dda.perp_wall_dist = NA;
	data->graphics.dda.plane_x = NA;
	data->graphics.dda.plane_y = NA;
	data->graphics.dda.pos_x = NA;
	data->graphics.dda.pos_y = NA;
	data->graphics.dda.ray_dir_x = NA;
	data->graphics.dda.ray_dir_y = NA;
	data->graphics.dda.side = NA;
	data->graphics.dda.side_dist_x = NA;
	data->graphics.dda.side_dist_y = NA;
	data->graphics.dda.step_x = NA;
	data->graphics.dda.step_y = NA;
	fill_dda_data(data);
}
