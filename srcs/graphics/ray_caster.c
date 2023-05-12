#include <cub3D.h>

/**
 * Loop until hitting a wall, check on x and y-direction which cell is the
 * 	closest and jump there.
 * Store which side (NSWE) has been hit for texturing.
 */
static void	dda_loop(t_general_data *data)
{
	data->graphics.calc.hit = 0;
	while (data->graphics.calc.hit == 0)
	{
		if (data->graphics.dda.side_dist_x < data->graphics.dda.side_dist_y)
		{
			data->graphics.dda.side_dist_x += data->graphics.dda.delta_dist_x;
			data->graphics.dda.map_x += data->graphics.dda.step_x;
			if (data->graphics.dda.step_x == -1)
				data->graphics.dda.side = WEST;
			if (data->graphics.dda.step_x == 1)
				data->graphics.dda.side = EAST;
		}
		else
		{
			data->graphics.dda.side_dist_y += data->graphics.dda.delta_dist_y;
			data->graphics.dda.map_y += data->graphics.dda.step_y;
			if (data->graphics.dda.step_y == -1)
				data->graphics.dda.side = NORTH;
			if (data->graphics.dda.step_y == 1)
				data->graphics.dda.side = SOUTH;
		}
		if (data->file_data.map_data.copy \
			[data->graphics.dda.map_y][data->graphics.dda.map_x] == '1')
			data->graphics.calc.hit = 1;
	}
}

/**
 * raycasting loop: goes through every x until reaching map width
 */
bool	cast_ray(t_general_data *data)
{
	int	x;

	draw_ceiling_floor(data);
	x = 0;
	while (x < data->graphics.width)
	{
		calc_ray(data, x);
		dda_loop(data);
		calc_wall(data);
		draw_3d(data, x);
		x++;
	}
	return (true);
}
