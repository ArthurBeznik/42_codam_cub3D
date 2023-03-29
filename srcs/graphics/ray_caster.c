#include <graphics.h>

bool draw_ray(t_general_data *data, double angle, int ray_x, int ray_y, int off_y, int off_x)
{
	int i;
	// int d_size;
	double x1;
	double y1;

	fprintf(stderr, "[draw]\t rx | ry : %d | %d\n", ray_x, ray_y);
	if (data == NULL)
	{
		fprintf(stderr, "offx | offy : %d | %d\n", off_x, off_y);
	}
	i = 0;
	x1 = 0;
	y1 = 0;
	// fprintf(stderr, "%f\n",)
	float distance = sqrt(pow(ray_x - data->file_data->player->x, 2) + pow(ray_y - data->file_data->player->y, 2));
	// float distance = sqrt((((int)ray_x - (int)data->file_data->player->x) * ((int)ray_x - (int)data->file_data->player->x))  + ((((int)ray_y - (int)data->file_data->player->y)) * ((int)ray_y - (int)data->file_data->player->y)));
	while (i < distance)
	// while (x1 != ray_x)
	{
		fprintf(stderr, "distance: %f\n", distance);
		// log_positions(data, "draw_dir", 'A');
		x1 = round(i * cos((angle))) + (data->file_data->player->x); // ? this need to be rounded, like ray_x and _y
		y1 = round(i * -sin((angle))) + (data->file_data->player->y);
		// log_val(data, "draw_dir", 'D'); // ? testing
		// log_val(data, "draw_dir", 'P'); // ? testing
		fprintf(stderr, "rx | ry : %d | %d\n", ray_x, ray_y); // ? testing
		fprintf(stderr, "x1 | y1: %f | %f\n", x1, y1); // ? testing
		if (!check_put_pixel(data, x1, y1))
			return (false);
		mlx_put_pixel(data->graphics->img, x1, y1, 0xFF0000FF);
		// mlx_put_pixel(data->graphics->img, ray_x, ray_y, 0xFF0000FF);
		if (y1 == round(ray_y) && x1 == round(ray_x))
		{
			fprintf(stderr, "here\n");
			return (true);
		} // ? only for horizontal lines
		// if (x1 == round(ray_x)) // ? only for vertical lines
		// 	return (true);
		// if (y1 == ray_y) // ? only for horizontal lines
		// 	return (true);
		i++;
	}
	return (true);
}

bool	ray_caster(t_general_data *data)
{
	if (data == NULL)
		log_val(data, "ray_caster", 'A');
	// check_vertical_gridlines(data);
	// check_horizontal_gridlines(data);
	return (true);
}

bool	test_ray(t_general_data *data)
{
	int 	i;
	double	ra;
	int 	dof;
	float 	ray_x;	// in pixels
	float 	ray_y;	// in pixels
	float 	off_y;
	float 	off_x;
	int		hit_x;	// in grid
	int		hit_y;	// in grid
	int		vx;
	int		vy;
	float 	dist_v;
	float 	dist_h;
	float	tan_var;

	i = 0;
	ra = data->file_data->player->angle;
	// ra = data->file_data->player->angle - DR * 15;
	// log_val(data, "ray_casting", 'A');
	// fprintf(stderr, "ra: %f\n", ra);
	// while (i < 15)
	while (i < 1)
	{
		// fprintf(stderr, "cos(ra) = %f\n", cos(ra));
		// fprintf(stderr, "TESTING1\n");
		fprintf(stderr, "\tVertical\n");
		dof = 0;
		dist_v = 100000;
		tan_var = tan(ra); // calculates the x and y components of the ray direction vector based on the pixel coordinates on the screen
		// fprintf(stderr, "aTan: %f\n", aTan);
		// log_val(data, "ray_caster", 'A');
		// log_val(data, "ray_caster", 'P');
		// if (ra > M_PI) // ? looking left
		// if (ra > M_PI)
		if (cos(ra) > 0.001)
		{
			// fprintf(stderr, "ra > M_PI\n");
			// fprintf(stderr, "cos(ra)\n", cos(ra));
			// fprintf(stderr, "before rx | ry : %f | %f\n", ray_x, ray_y);
			// log_val(data, "ray_caster", 'P');
			ray_x = (((int)data->file_data->player->x >> 6) << 6) + 64;
			ray_y = (data->file_data->player->x - ray_x) * tan_var + data->file_data->player->y;
			off_x = 64;
			off_y = -off_x * tan_var;
			// fprintf(stderr, "after rx | ry : %f | %f\n", ray_x, ray_y);
		}
		// else if (cos(degToRad(ra)) < -0.001)
		else if (cos(ra) < -0.001)
		// else if (ra < M_PI) // ? looking right
		{
			// fprintf(stderr, "ra < M_PI\n");
			// fprintf(stderr, "before rx | ry : %f | %f\n", ray_x, ray_y);
			ray_x = (((int)data->file_data->player->x >> 6) << 6) - 0.0001;
			ray_y = (data->file_data->player->x - ray_x) * tan_var + data->file_data->player->y;
			off_x = -64;
			off_y = -off_x * tan_var;
			// fprintf(stderr, "after rx | ry : %f | %f\n", ray_x, ray_y);
		}
		// else if (ra == 0 || ra == M_PI) // ? looking up or down
		else // ? looking up or down
		{
			// fprintf(stderr, "ra = 0 || ra = M_PI\n");
			fprintf(stderr, "V - up down => no hit on vertical\n");
			ray_x = data->file_data->player->x;
			ray_y = data->file_data->player->y;
			dof = 8;
			// fprintf(stderr, "rx | ry : %f | %f\n", ray_x, ray_y);
		}
		// fprintf(stderr, "rx | ry : %f | %f\n", ray_x, ray_y);
		// fprintf(stderr, "col | row : %d | %d\n", data->file_data->map_data->col, data->file_data->map_data->row);
		while (dof < 8)
		{
			// fprintf(stderr, "dof < 8\n");
			fprintf(stderr, "rx | ry : %f | %f\n", ray_x, ray_y);
			// hit_x = (int)(ray_x) >> 6; // ? x where the ray hits a wall or line
			if (ray_x == 0)
				hit_x = 0;
			else
				hit_x = (int)(ray_x) >> 6; // ? x where the ray hits a wall or line
			if (ray_y == 0)
				hit_y = 0;
			else
				hit_y = (int)(ray_y) >> 6; // ? y where the ray hits a wall or line
			fprintf(stderr, "hit_x | hit_y : %d | %d\n", hit_x, hit_y);
			// fprintf(stderr, "hit_x | hit_y (value) : %d | %d (%c)\n", hit_x, hit_y, data->file_data->map_data->copy[hit_y][hit_x]);
			if ((hit_x >= 0 && hit_y >= 0) \
				&& ((hit_x < data->file_data->map_data->row && hit_y < data->file_data->map_data->col)) \
				&& data->file_data->map_data->copy[hit_y][hit_x] == '1')
			{
				fprintf(stderr, "\thit wall\n");
				dof = 8;
				dist_v = cos(ra) * (ray_x - data->file_data->player->x) - sin(ra) * (ray_y - data->file_data->player->y);
				fprintf(stderr, "dist_v : %f\n", dist_v);
			}
			else
			{
				fprintf(stderr, "\tV - check next horizontal\n");
				ray_x += off_x;
				ray_y += off_y;
				if (ray_y < 0 || ray_x < 0 || ray_x > data->graphics->width || ray_y > data->graphics->height)
				{
					fprintf(stderr, "Negative rx or ry, stopping\n");
					dof = 8;
				}
				dof += 1;
				// fprintf(stderr, "rx | ry : %d | %d\n", ray_x, ray_y);
			}
		}

		fprintf(stderr, "\tHorizontal\n");

		vx = ray_x;
		vy = ray_y;

		dof = 0;
		dist_h = 100000;
		// float aTan = -1 / tan(ra); // calculates the x and y components of the ray direction vector based on the pixel coordinates on the screen
		tan_var = 1.0 / tan_var; // calculates the x and y components of the ray direction vector based on the pixel coordinates on the screen
		// fprintf(stderr, "aTan: %f\n", aTan);

		// if (ra > M_PI) // ? looking up
		if (sin(ra) > 0.001)
		{
			// fprintf(stderr, "ra > M_PI\n");
			ray_y = (((int)data->file_data->player->y >> 6) << 6) - 0.0001;
			ray_x = (data->file_data->player->y - ray_y) * tan_var + data->file_data->player->x;
			off_y = -64;
			off_x = -off_y * tan_var;
		}
		// if (ra < M_PI) // ? looking down
		else if (sin(ra) < -0.001)
		{
			// fprintf(stderr, "ra < M_PI\n");
			ray_y = (((int)data->file_data->player->y >> 6) << 6) + 64;
			ray_x = (data->file_data->player->y - ray_y) * tan_var + data->file_data->player->x;
			off_y = 64;
			off_x = -off_y * tan_var;
		}
		// if (ra == 0 || ra == M_PI) // ? looking left or right
		else // ? looking left or right
		{
			// fprintf(stderr, "ra = 0 || ra = M_PI\n");
			fprintf(stderr, "H - left right => no hit on horizontal\n");
			ray_x = data->file_data->player->x;
			ray_y = data->file_data->player->y;
			dof = 8;
		}
		// fprintf(stderr, "col | row : %d | %d\n", data->file_data->map_data->col, data->file_data->map_data->row);
		while (dof < 8)
		{
			// fprintf(stderr, "dof < 8\n");
			fprintf(stderr, "ray_x | ray_y : %f | %f\n", round(ray_x), round(ray_y));
			fprintf(stderr, "dof : %d\n", dof);
			// if (ray_x == 0)
			// 	hit_x = 0;
			// else
				hit_x = (int)(ray_x) >> 6; // ? x where the ray hits a wall or line
			// if (ray_y == 0)
			// 	hit_y = 0;
			// else
				hit_y = (int)(ray_y) >> 6; // where the ray hits a wall or line
			fprintf(stderr, "hit_x | hit_y : %d | %d\n", hit_x, hit_y);
			// fprintf(stderr, "col | row : %lld | %lld\n", data->file_data->map_data->col, data->file_data->map_data->row);
			if ((hit_x >= 0 && hit_y >= 0) \
				&& ((hit_x < data->file_data->map_data->row && hit_y < data->file_data->map_data->col)) \
				&& data->file_data->map_data->copy[hit_y][hit_x] == '1')
			{
				fprintf(stderr, "hit_x | hit_y (value) : %d | %d (%c)\n", hit_x, hit_y, data->file_data->map_data->copy[hit_y][hit_x]);
				fprintf(stderr, "\thit wall\n");
				dof = 8;
				dist_h = cos(ra) * (ray_x - data->file_data->player->y) - sin(ra) * (ray_y - data->file_data->player->y);
				fprintf(stderr, "dist_h : %f\n", dist_h);
			}
			else
			{
				// fprintf(stderr, "\tdid not hit\n");
				ray_x += off_x;
				ray_y += off_y;
				if (ray_y < 0 || ray_x < 0 || ray_x > data->graphics->width || ray_y > data->graphics->height)
				{
					fprintf(stderr, "Negative rx or ry, stopping\n");
					dof = 8;
				}
				dof += 1;
				// fprintf(stderr, "rx | ry : %d | %d\n", ray_x, ray_y);
			}
		}
		i++;

		fprintf(stderr, "dist_v | dist_h : %f | %f\n", dist_v, dist_h);
		if (dist_v < dist_h)
		{
			ray_x = vx;
			ray_y = vy;
			dist_h = dist_v;
		} // horizontal hit first

		// ra+=DR;

		draw_ray(data, ra, ray_x, ray_y, off_x, off_y);
	}
	return (true);
}