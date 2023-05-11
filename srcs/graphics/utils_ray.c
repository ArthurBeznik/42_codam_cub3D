#include <cub3D.h>

/**
 * Initialise ray position and direction.
 * Based on the ray direction, calculate the length of the ray from one x 
 * 	or y-side to next x or y-side.
 */
void	init_ray_vars(t_general_data *data, int x)
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

/**
 * Calculate the exact value where the wall was hit, required to know which
 * 	x-coord of the texture we have to use.
 */
void	get_hit_wall_value(t_general_data *data)
{
	if (data->graphics.dda.side == WEST || data->graphics.dda.side == EAST)
		data->graphics.calc.wall_x = data->graphics.dda.pos_y \
			+ data->graphics.dda.perp_wall_dist * data->graphics.dda.ray_dir_y;
	else
		data->graphics.calc.wall_x = data->graphics.dda.pos_x \
			+ data->graphics.dda.perp_wall_dist * data->graphics.dda.ray_dir_x;
	data->graphics.calc.wall_x -= floor((data->graphics.calc.wall_x));
	data->graphics.calc.tex_x = (int)(data->graphics.calc.wall_x \
		* (double)(PIXELS));
	if (data->graphics.dda.side == EAST || data->graphics.dda.side == NORTH)
		data->graphics.calc.tex_x = PIXELS - data->graphics.calc.tex_x - 1;
}

/**
 * Based on the side the ray is facing, calculate the distance of the ray
 * 	to the wall (perpendicular).
 * Based on this distance, calculate the height of the line to be drawn.
 * Based on this height, calculate start and end positions of the drawing,
 *  we draw from the center of the screen (i.e. / 2), if the other points 
 * 	are outside of the screen, they are capped to 0 to h-1.
 */
void	get_perp_wall_dist(t_general_data *data)
{
	if (data->graphics.dda.side == WEST || data->graphics.dda.side == EAST)
		data->graphics.dda.perp_wall_dist = (data->graphics.dda.side_dist_x \
			- data->graphics.dda.delta_dist_x);
	else
		data->graphics.dda.perp_wall_dist = (data->graphics.dda.side_dist_y \
			- data->graphics.dda.delta_dist_y);
	data->graphics.calc.line_height = (int)(data->graphics.dda.h \
		/ data->graphics.dda.perp_wall_dist);
	data->graphics.calc.pitch = 100;
	data->graphics.calc.draw_start = -data->graphics.calc.line_height \
		/ 2 + data->graphics.dda.h / 2 + data->graphics.calc.pitch;
	if (data->graphics.calc.draw_start < 0)
		data->graphics.calc.draw_start = 0;
	data->graphics.calc.draw_end = data->graphics.calc.line_height \
		/ 2 + data->graphics.dda.h / 2 + data->graphics.calc.pitch;
	if (data->graphics.calc.draw_end >= data->graphics.dda.h)
		data->graphics.calc.draw_end = data->graphics.dda.h - 1;
}

void	calc_walls(t_general_data *data)
{
	get_perp_wall_dist(data);
	get_hit_wall_value(data);
}
