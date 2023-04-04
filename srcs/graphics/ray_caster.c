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
	// ray_len = sqrt(pow(x - data->file_data->player->x, 2) + pow(y - data->file_data->player->y, 2));		 // ? these two ray_len give the same result
	ray_len = cos(angle) * (x - data->file_data->player->x) - sin(angle) * (y - data->file_data->player->y); // ? these two ray_len give the same result
	// fprintf(stderr, "ray_len: %f\n", ray_len); // ? testing
	// fprintf(stderr, "rounded ray_len: %f\n", roundf(ray_len)); // ? testing
	// fprintf(stderr, "[draw]\t rx | ry : %d | %d\n", x, y); // ? testing
	while (i < roundf(ray_len)) // ! stops on the wall
	// while (i < ray_len) // ! stops after the wall ~= 1px
	// while (i < ray_len - 1) // ! stops before the wall ~= 1px
	{
		x1 = round(i * cos((angle))) + (data->file_data->player->x);  // ? this need to be rounded, like x and _y to have grid values
		y1 = round(i * -sin((angle))) + (data->file_data->player->y); // ? this need to be rounded, like x and _y to have grid values
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
	int dof;
	float tan_var;
	t_ray **raymond;

	i = 0;
	if (!init_rays(data))
		return (false);
	raymond = data->graphics->ray;
	// angle = data->file_data->player->angle; // ? only for one ray
	angle = data->file_data->player->angle + (30 * DR); // ? (30 * DR) is the FOV angle in radian, thus 30 is the angle in degrees
	// log_val(data, "ray_casting", 'A');
	while (i < NB_RAYS)
	{
		raymond[i]->angle = angle;
		// fprintf(stderr, "angle | raymond angle : %f | %f\n", angle, raymond[i]->angle);
		// fprintf(stderr, "raymond angle: %f", raymond[i]->angle);
		// fprintf(stderr, "cos(angle) = %f\n", cos(angle));
		// fprintf(stderr, "\tVertical\n");
		dof = 0;
		raymond[i]->dist_v = 100000;
		tan_var = tan(angle); // calculates the x and y components of the ray direction vector based on the pixel coordinates on the screen
		// fprintf(stderr, "aTan: %f\n", aTan);
		// log_val(data, "ray_caster", 'A');
		// log_val(data, "ray_caster", 'P');
		if (cos(angle) > 0.001) // ? (angle > M_PI) => looking left
		{
			// fprintf(stderr, "angle > M_PI\n");
			// fprintf(stderr, "before rx | ry : %f | %f\n", x, y);
			// log_val(data, "ray_caster", 'P');
			raymond[i]->x = (((int)data->file_data->player->x >> 6) << 6) + 64;
			raymond[i]->y = (data->file_data->player->x - raymond[i]->x) * tan_var + data->file_data->player->y;
			raymond[i]->off_x = 64;
			raymond[i]->off_y = -raymond[i]->off_x * tan_var;
			// fprintf(stderr, "after rx | ry : %f | %f\n", x, y); // ? testing
			// fprintf(stderr, "off_x | off_y : %f | %f\n", raymond[i]->off_x, raymond[i]->off_y); // ? testing
		}
		else if (cos(angle) < -0.001) // ? (angle < M_PI) => looking right
		{
			// fprintf(stderr, "angle < M_PI\n"); // ? testing
			// fprintf(stderr, "before rx | ry : %f | %f\n", x, y); // ? testing
			raymond[i]->x = (((int)data->file_data->player->x >> 6) << 6) - 0.0001;
			raymond[i]->y = (data->file_data->player->x - raymond[i]->x) * tan_var + data->file_data->player->y;
			raymond[i]->off_x = -64;
			raymond[i]->off_y = -raymond[i]->off_x * tan_var;
			// fprintf(stderr, "after rx | ry : %f | %f\n", x, y); // ? testing
			// fprintf(stderr, "off_x | off_y : %f | %f\n", raymond[i]->off_x, raymond[i]->off_y); // ? testing
		}
		else // ? (angle == 0 || angle == M_PI) => looking up or down
		{
			// fprintf(stderr, "V - up down => no hit on vertical\n");
			raymond[i]->x = data->file_data->player->x;
			raymond[i]->y = data->file_data->player->y;
			dof = 8;
			// fprintf(stderr, "rx | ry : %f | %f\n", x, y);
		}
		// fprintf(stderr, "rx | ry : %f | %f\n", x, y);
		// fprintf(stderr, "col | row : %d | %d\n", data->file_data->map_data->col, data->file_data->map_data->row);
		while (dof < 8)
		{
			// fprintf(stderr, "dof < 8\n");
			// fprintf(stderr, "rx | ry : %f | %f\n", raymond[i]->x, raymond[i]->y);
			// hit_x = (int)(x) >> 6; // ? x where the ray hits a wall or line
			raymond[i]->hit_x = (int)(raymond[i]->x) >> 6; // ? x where the ray hits a wall or line
			raymond[i]->hit_y = (int)(raymond[i]->y) >> 6; // ? y where the ray hits a wall or line
			// fprintf(stderr, "hit_x | hit_y : %d | %d\n", hit_x, hit_y);
			// fprintf(stderr, "hit_x | hit_y (value) : %d | %d (%c)\n", hit_x, hit_y, data->file_data->map_data->copy[hit_y][hit_x]);
			if ((raymond[i]->hit_x >= 0 && raymond[i]->hit_y >= 0) && ((raymond[i]->hit_x < data->file_data->map_data->row && raymond[i]->hit_y < data->file_data->map_data->col)) && data->file_data->map_data->copy[raymond[i]->hit_y][raymond[i]->hit_x] == '1')
			{
				// fprintf(stderr, "\thit wall\n");
				dof = 8;
				raymond[i]->dist_v = cos(angle) * (raymond[i]->x - data->file_data->player->x) - sin(angle) * (raymond[i]->y - data->file_data->player->y);
				// fprintf(stderr, "dist_v : %f\n", dist_v);
			}
			else
			{
				// fprintf(stderr, "\tV - check next horizontal\n");
				raymond[i]->x += raymond[i]->off_x;
				raymond[i]->y += raymond[i]->off_y;
				if (raymond[i]->y < 0 || raymond[i]->x < 0 || raymond[i]->x > data->graphics->width || raymond[i]->y > data->graphics->height)
				{
					// fprintf(stderr, "Negative rx or ry, stopping\n");
					dof = 8;
				}
				dof += 1;
				// fprintf(stderr, "rx | ry : %d | %d\n", x, y);
			}
		}

		// fprintf(stderr, "\tHorizontal\n");

		raymond[i]->vx = raymond[i]->x;
		raymond[i]->vy = raymond[i]->y;

		dof = 0;
		raymond[i]->dist_h = 100000;
		// float aTan = -1 / tan(angle); // calculates the x and y components of the ray direction vector based on the pixel coordinates on the screen
		tan_var = 1.0 / tan_var; // calculates the x and y components of the ray direction vector based on the pixel coordinates on the screen
		// fprintf(stderr, "aTan: %f\n", aTan);
		if (sin(angle) > 0.001) // ? (angle > M_PI) => looking up
		{
			// fprintf(stderr, "angle > M_PI\n");
			raymond[i]->y = (((int)data->file_data->player->y >> 6) << 6) - 0.0001;
			raymond[i]->x = (data->file_data->player->y - raymond[i]->y) * tan_var + data->file_data->player->x;
			raymond[i]->off_y = -64;
			raymond[i]->off_x = -raymond[i]->off_y * tan_var;
		}
		else if (sin(angle) < -0.001) // ? (angle < M_PI) => looking down
		{
			// fprintf(stderr, "angle < M_PI\n");
			raymond[i]->y = (((int)data->file_data->player->y >> 6) << 6) + 64;
			raymond[i]->x = (data->file_data->player->y - raymond[i]->y) * tan_var + data->file_data->player->x;
			raymond[i]->off_y = 64;
			raymond[i]->off_x = -raymond[i]->off_y * tan_var;
		}
		else // ? (angle == 0 || angle == M_PI) => looking left or right
		{
			// fprintf(stderr, "H - left right => no hit on horizontal\n");
			raymond[i]->x = data->file_data->player->x;
			raymond[i]->y = data->file_data->player->y;
			dof = 8;
		}
		// fprintf(stderr, "col | row : %d | %d\n", data->file_data->map_data->col, data->file_data->map_data->row);
		while (dof < 8)
		{
			// fprintf(stderr, "dof < 8\n");
			// fprintf(stderr, "x | y : %f | %f\n", round(x), round(y));
			// fprintf(stderr, "dof : %d\n", dof);
			raymond[i]->hit_x = (int)(raymond[i]->x) >> 6; // ? x where the ray hits a wall or line
			raymond[i]->hit_y = (int)(raymond[i]->y) >> 6; // where the ray hits a wall or line
			// fprintf(stderr, "hit_x | hit_y : %d | %d\n", raymond[i]->hit_x, raymond[i]->hit_y);
			// fprintf(stderr, "col | row : %lld | %lld\n", data->file_data->map_data->col, data->file_data->map_data->row);
			if ((raymond[i]->hit_x >= 0 && raymond[i]->hit_y >= 0) && ((raymond[i]->hit_x < data->file_data->map_data->row && raymond[i]->hit_y < data->file_data->map_data->col)) && data->file_data->map_data->copy[raymond[i]->hit_y][raymond[i]->hit_x] == '1')
			{
				// fprintf(stderr, "hit_x | hit_y (value) : %d | %d (%c)\n", hit_x, hit_y, data->file_data->map_data->copy[hit_y][hit_x]);
				// fprintf(stderr, "\thit wall\n");
				dof = 8;
				raymond[i]->dist_h = cos(angle) * (raymond[i]->x - data->file_data->player->x) - sin(angle) * (raymond[i]->y - data->file_data->player->y);
				// fprintf(stderr, "dist_h : %f\n", dist_h);
			}
			else
			{
				// fprintf(stderr, "\tdid not hit\n");
				raymond[i]->x += raymond[i]->off_x;
				raymond[i]->y += raymond[i]->off_y;
				if (raymond[i]->y < 0 || raymond[i]->x < 0 || raymond[i]->x > data->graphics->width || raymond[i]->y > data->graphics->height)
				{
					// fprintf(stderr, "Negative rx or ry, stopping\n");
					dof = 8;
				}
				dof += 1;
				// fprintf(stderr, "rx | ry : %d | %d\n", x, y);
			}
		}
		// fprintf(stderr, "dist_v | dist_h : %f | %f\n", dist_v, dist_h);
		if (raymond[i]->dist_v < raymond[i]->dist_h)
		{
			raymond[i]->x = raymond[i]->vx;
			raymond[i]->y = raymond[i]->vy;
			raymond[i]->dist_h = raymond[i]->dist_v;
		} // horizontal hit first

		raymond[i]->angle = angle;
		angle -= (DR * 2); // ? when drawing multiple rays, we need to decrement the angle of each ray

		// fprintf(stderr, "rx | ry : %f | %f\n", raymond[i]->x, raymond[i]->y); // ? testing
		draw_ray(data, raymond[i]->angle, raymond[i]->x, raymond[i]->y);
		i++;
	}
	return (true);
}