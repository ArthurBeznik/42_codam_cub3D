#include <graphics.h>

bool	draw_3d_walls(t_general_data *data, t_ray *raymond, int i)
{
	float	ca;
	int		line_h;
	int		line_off;
	int		n;
	int		x1;
	int		y1;

	/**
	 * ! fixing fish eye
	 * 	ca: angle between the player's direction and the ray's direction
	 * 	dist_h: horizontal distance between the player and the wall the ray hits
	 *  line_h: height of the wall that the ray hits
	 * 	line_off: offset from the center of the screen to the top of the wall
	 * 		If the wall is taller, the offset will be negative and the wall will start off the screen at the top. 
	 * 		If the wall is shorter, the offset will be positive and the wall will start on the screen.
	*/
	ca = data->file_data->player->angle - raymond->angle;
	// fprintf(stderr, "[draw_3d_walls]\tca: %f\n", ca); // ? testing
	// fprintf(stderr, "[draw_3d_walls]\tpa: %f\n", data->file_data->player->angle); // ? testing
	// fprintf(stderr, "[draw_3d_walls]\tra: %f\n", raymond->angle); // ? testing
	if (ca < 0)
		ca += RESET_ANGLE;
	if (ca > 2 * M_PI)
		ca -= RESET_ANGLE;
	raymond->dist_h = raymond->dist_h * cos(ca);
	line_h = (PIXELS * 320) / (raymond->dist_h);
	if (line_h > 320)
		line_h = 320;
	line_off = 160 - (line_h >> 1);
	// fprintf(stderr, "[draw_3d_walls]\tline_off: %d\n", line_off); // ? testing

	n = 0;
	while (n < line_h)
	{
		// log_val(data, "draw_3d_walls", 'A');
		x1 = i * 8; // ! on x, draw every 8th pixel
		y1 = line_off + n; // ! on y, starting at line_off, draw every n pixels until line_h
		// fprintf(stderr, "[draw_3d_walls]\tx1 | y1: %d | %d\n", x1, y1); // ? testing
		// log_val(data, "draw_3d_walls", 'D'); // ? testing
		// log_val(data, "draw_3d_walls", 'P'); // ? testing
		if (!check_put_pixel(data, x1, y1))
			return (false);
		mlx_put_pixel(data->graphics->img_3d, x1, y1, 0x00FF00FF);
		n++;
	}
	return (true);
}

bool	draw_ray(t_general_data *data, double angle, float x, float y)
{
	int		i;
	float	x1;
	float	y1;
	float	ray_len;

	i = 0;
	x1 = 0;
	y1 = 0;
	// ray_len = sqrt(pow(x - data->file_data->player->x, 2) + pow(y - data->file_data->player->y, 2));		 // ! these two ray_len give the same result
	ray_len = cos(angle) * (x - data->file_data->player->x) - sin(angle) * (y - data->file_data->player->y); // ! these two ray_len give the same result
	// fprintf(stderr, "[draw_ray]\tray_len: %f\n", ray_len); // ? testing
	// fprintf(stderr, "[draw_ray]\trounded ray_len: %f\n", roundf(ray_len)); // ? testing
	// fprintf(stderr, "[draw_ray]\t rx | ry : %d | %d\n", x, y); // ? testing
	while (i < roundf(ray_len)) // ! stops on the wall
	// while (i < ray_len) // ! stops after the wall ~= 1px
	// while (i < ray_len - 1) // ! stops before the wall ~= 1px
	{
		x1 = round(i * cos((angle))) + (data->file_data->player->x); // ! this need to be rounded, like x and _y to have grid values
		y1 = round(i * -sin((angle))) + (data->file_data->player->y); // ! this need to be rounded, like x and _y to have grid values
		// log_val(data, "draw_ray", 'D'); // ? testing
		// log_val(data, "draw_ray", 'P'); // ? testing
		// fprintf(stderr, "[draw_ray]\trx | ry : %d | %d\n", x, y); // ? testing
		// fprintf(stderr, "[draw_ray]\tx1 | y1: %f | %f\n", x1, y1); // ? testing
		if (!check_put_pixel(data, x1, y1))
			return (false);
		mlx_put_pixel(data->graphics->img, x1, y1, 0xFF0000FF);
		i++;
	}
	return (true);
}

/**
 * radian = degree * M_PI / 180.0
 */
bool	ray_caster(t_general_data *data)
{
	int		i;
	float	angle;
	t_ray	**raymond;

	i = 0;
	raymond = data->graphics->ray;
	angle = data->file_data->player->angle + (NB_RAYS * DR); // ! (NB_RAYS * DR) is the FOV angle in radian
	// log_val(data, "ray_caster", 'A'); // ? testing
	while (i < NB_RAYS)
	{
		vertical_ray(data, raymond[i], angle);
		horizontal_ray(data, raymond[i], angle);
		// fprintf(stderr, "[ray_caster] dist_v | dist_h : \t%f | %f\n", raymond[i]->dist_v, raymond[i]->dist_h); // ? testing

		// fprintf(stderr, "[ray_caster] rx | ry : \t%f | %f\n", raymond[i]->x, raymond[i]->y); // ? testing
		if (!draw_ray(data, raymond[i]->angle, raymond[i]->x, raymond[i]->y))
			return (error_msg("draw_ray"));

		/**
		 * ! the "3D" window size will be 320/160
		*/
		if (!draw_3d_walls(data, raymond[i], i))
			return (error_msg("draw_3d"));

		angle -= (DR * 2); // ! when drawing multiple rays, we need to decrement the angle of each ray
		i++;
	}
	return (true);
}
