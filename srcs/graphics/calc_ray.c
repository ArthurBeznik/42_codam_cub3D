#include <cub3D.h>

/**
 * Check ray x direction (left/right) and ray y direction (up/down) 
 * 	and set step x and y accordingly.
 * Step is the direction to step in x or y-direction (= 1 or -1).
*/
static void	check_ray_dir(t_general_data *data)
{
	if (data->graphics.dda.ray_dir_x < 0)
	{
		data->graphics.dda.step_x = -1;
		data->graphics.dda.side_dist_x = (data->graphics.dda.pos_x \
			- data->graphics.dda.map_x) * data->graphics.dda.delta_dist_x;
	}
	else
	{
		data->graphics.dda.step_x = 1;
		data->graphics.dda.side_dist_x = (data->graphics.dda.map_x + 1.0 \
			- data->graphics.dda.pos_x) * data->graphics.dda.delta_dist_x;
	}
	if (data->graphics.dda.ray_dir_y < 0)
	{
		data->graphics.dda.step_y = -1;
		data->graphics.dda.side_dist_y = (data->graphics.dda.pos_y \
			- data->graphics.dda.map_y) * data->graphics.dda.delta_dist_y;
	}
	else
	{
		data->graphics.dda.step_y = 1;
		data->graphics.dda.side_dist_y = (data->graphics.dda.map_y + 1.0 \
			- data->graphics.dda.pos_y) * data->graphics.dda.delta_dist_y;
	}
}

/**
 * Initialise ray position and direction.
 * Based on the ray direction, calculate the length of the ray from one x 
 * 	or y-side to next x or y-side.
 */
static void	init_ray_vars(t_general_data *data, int x)
{
	data->graphics.dda.camera_x = 2 * x / (double)data->graphics.dda.w - 1;
	data->graphics.dda.ray_dir_x = data->graphics.dda.dir_x \
		+ data->graphics.dda.plane_x * data->graphics.dda.camera_x;
	data->graphics.dda.ray_dir_y = data->graphics.dda.dir_y \
		+ data->graphics.dda.plane_y * data->graphics.dda.camera_x;
	data->graphics.dda.map_x = (int)data->graphics.dda.pos_x;
	data->graphics.dda.map_y = (int)data->graphics.dda.pos_y;
	if (data->graphics.dda.ray_dir_x == 0)
		data->graphics.dda.delta_dist_x = 1e30;
	else
		data->graphics.dda.delta_dist_x = \
			fabs(1 / data->graphics.dda.ray_dir_x);
	if (data->graphics.dda.ray_dir_y == 0)
		data->graphics.dda.delta_dist_y = 1e30;
	else
		data->graphics.dda.delta_dist_y = \
			fabs(1 / data->graphics.dda.ray_dir_y);
}

void	calc_ray(t_general_data *data, int x)
{
	init_ray_vars(data, x);
	check_ray_dir(data);
}
