#include <graphics.h>

bool draw_ray(t_general_data *data, double angle, float x, float y)
{
	int i;
	float x1;
	float y1;
	float ray_len;

	i = 0;
	x1 = 0;
	y1 = 0;
	// ray_len = sqrt(pow(x - data->file_data->player->x, 2) + pow(y - data->file_data->player->y, 2));		 // ! these two ray_len give the same result
	ray_len = cos(angle) * (x - data->file_data->player->x) - sin(angle) * (y - data->file_data->player->y); // ! these two ray_len give the same result
	// fprintf(stderr, "ray_len: %f\n", ray_len); // ? testing
	// fprintf(stderr, "rounded ray_len: %f\n", roundf(ray_len)); // ? testing
	// fprintf(stderr, "[draw]\t rx | ry : %d | %d\n", x, y); // ? testing
	while (i < roundf(ray_len)) // ! stops on the wall
	// while (i < ray_len) // ! stops after the wall ~= 1px
	// while (i < ray_len - 1) // ! stops before the wall ~= 1px
	{
		x1 = round(i * cos((angle))) + (data->file_data->player->x);  // ! this need to be rounded, like x and _y to have grid values
		y1 = round(i * -sin((angle))) + (data->file_data->player->y); // ! this need to be rounded, like x and _y to have grid values
		// log_val(data, "draw_dir", 'D'); // ? testing
		// log_val(data, "draw_dir", 'P'); // ? testing
		// fprintf(stderr, "rx | ry : %d | %d\n", x, y); // ? testing
		// fprintf(stderr, "x1 | y1: %f | %f\n", x1, y1); // ? testing
		if (!check_put_pixel(data, x1, y1))
			return (false);
		mlx_put_pixel(data->graphics->img, x1, y1, 0xFF0000FF);
		i++;
	}
	return (true);
}

bool init_rays(t_general_data *data)
{
	int i;
	t_ray **raymond;

	i = 0;
	raymond = (t_ray **)malloc(sizeof(t_ray) * NB_RAYS);
	if (!raymond)
		return (error_msg("Malloc raymond struct"));
	while (i < NB_RAYS)
	{
		raymond[i] = (t_ray *)malloc(sizeof(t_ray));
		if (!raymond)
			// ! free raymond
			return (error_msg("Malloc raymond ptr"));
		raymond[i]->x = 999;
		raymond[i]->y = 999;
		raymond[i]->angle = 999;
		raymond[i]->off_x = 999;
		raymond[i]->off_y = 999;
		raymond[i]->hit_x = 999;
		raymond[i]->hit_y = 999;
		raymond[i]->vx = 999;
		raymond[i]->vy = 999;
		raymond[i]->dist_v = 999;
		raymond[i]->dist_h = 999;
		raymond[i]->tan_var = 999;
		raymond[i]->dof = 999;
		i++;
	}
	data->graphics->ray = raymond;
	return (true);
}

/**
 * radian = degree * M_PI / 180.0
 */
bool ray_caster(t_general_data *data)
{
	int i;
	float angle;
	// int dof;
	// float tan_var;
	t_ray **raymond;

	i = 0;
	if (!init_rays(data))
		return (false);
	raymond = data->graphics->ray;
	// angle = data->file_data->player->angle; // ! only for one ray
	angle = data->file_data->player->angle + (30 * DR); // ! (30 * DR) is the FOV angle in radian, thus 30 is the angle in degrees
	// log_val(data, "ray_casting", 'A'); // ? testing
	while (i < NB_RAYS)
	// while (i < 1)
	{
		vertical_ray(data, raymond[i], angle);
		horizontal_ray(data, raymond[i], angle);
		// fprintf(stderr, "dist_v | dist_h : %f | %f\n", raymond[i]->dist_v, raymond[i]->dist_h);
		if (raymond[i]->dist_v < raymond[i]->dist_h)
		{
			raymond[i]->x = raymond[i]->vx;
			raymond[i]->y = raymond[i]->vy;
			raymond[i]->dist_h = raymond[i]->dist_v;
		} // horizontal hit first

		// raymond[i]->angle = angle;
		angle -= (DR * 2); // ! when drawing multiple rays, we need to decrement the angle of each ray

		// fprintf(stderr, "rx | ry : %f | %f\n", raymond[i]->x, raymond[i]->y); // ? testing
		draw_ray(data, raymond[i]->angle, raymond[i]->x, raymond[i]->y);

		int ca = data->file_data->player->angle - raymond[i]->angle;
		raymond[i]->dist_h = raymond[i]->dist_h * cos(ca); // fix fisheye
		int lineH = (PIXELS * 320) / (raymond[i]->dist_h);
		if (lineH > 320)
		{
			lineH = 320;
		}								  // line height and limit
		int lineOff = 160 - (lineH >> 1); // line offset
		// fprintf(stderr, "here\n"); // ? testing
		fprintf(stderr, "lineOff: %d\n", lineOff); // ? testing

		// glVertex2i(r * 8 + 530, lineOff);
		// mlx_put_pixel(data->graphics->img_3d, i * 8 + 530, lineOff, 0xFF0000FF);
		int n = 0;
		while (n < lineH - lineOff)
		{
			// log_positions(data, "draw_dir", 'A');
			// int x1 = (n * cos(angle)) + (i * 8 + 500);
			int x1 = i * 8;
			// int y1 = (n * -sin(angle)) + lineOff;
			int y1 = (n * -sin(angle)) + 500;
			fprintf(stderr, "x1 | y1: %d | %d\n", x1, y1); // ? testing
			// log_positions(data, "draw_dir", 'D'); // ? testing
			// log_positions(data, "draw_dir", 'P'); // ? testing
			if (!check_put_pixel(data, x1, y1))
				return (false);	
			mlx_put_pixel(data->graphics->img_3d, x1, y1, 0x00FF00FF);
			// mlx_put_pixel(img, x1 - 1, y1 - 1, 0x00FF00FF);
			// mlx_put_pixel(img, x1 + 1, y1 + 1, 0x00FF00FF);
			n++;
		}

		// glVertex2i(r * 8 + 530, lineOff + lineH);
		// mlx_put_pixel(data->graphics->img_3d, i * 8 + 530, lineOff + lineH, 0xFF0000FF);
		// n = 0;
		// while (n < 64)
		// {
		// 	// log_positions(data, "draw_dir", 'A');
		// 	int x1 = (n * cos(angle)) + (i * 8 + 530);
		// 	int y1 = (n * -sin(angle)) + (lineOff + lineH);
		// 	// fprintf(stderr, "x1 | y1: %f | %f\n", x1, y1); // ? testing
		// 	// log_positions(data, "draw_dir", 'D'); // ? testing
		// 	// log_positions(data, "draw_dir", 'P'); // ? testing
		// 	if (!check_put_pixel(data, x1, y1))
		// 		return (false);	
		// 	mlx_put_pixel(data->graphics->img_3d, x1, y1, 0x00FF00FF);
		// 	// mlx_put_pixel(img, x1 - 1, y1 - 1, 0x00FF00FF);
		// 	// mlx_put_pixel(img, x1 + 1, y1 + 1, 0x00FF00FF);
		// 	n++;
		// }
		i++;
	}
	return (true);
}
