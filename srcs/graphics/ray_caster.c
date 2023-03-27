#include <graphics.h>

bool draw_ray(t_general_data *data, double angle, int ray_x, int ray_y, int off_y, int off_x)
{
	int i;
	int d_size;
	double x1;
	double y1;

	// fprintf(stderr, "rx | ry : %d | %d\n", ray_x, ray_y);
	// mlx_put_pixel(data->graphics->img, ray_x, ray_y, 0x00FF0090);
	d_size = 64;
	i = 0;
	x1 = 0;
	while (i < 8 * PIXELS)
	// while (x1 != ray_x)
	{
		// log_positions(data, "draw_dir", 'A');
		x1 = (i * cos((angle))) + (data->file_data->player->x);
		y1 = (i * sin((angle))) + (data->file_data->player->y);
		// log_positions(data, "draw_dir", 'D'); // ? testing
		// log_positions(data, "draw_dir", 'P'); // ? testing
		// if (!check_put_pixel(data, x1, y1))
		// 	return (false);
		mlx_put_pixel(data->graphics->img, x1, y1, 0xFF0000FF);
		i++;
	}
	// fprintf(stderr, "x1 | y1: %f | %f\n", x1, y1); // ? testing
	return (true);
}

void ray_casting(t_general_data *data)
{
	int i;
	double ra;
	int dof;
	int ray_x;
	int ray_y;
	int off_y;
	int off_x;

	i = 0;
	ra = data->file_data->player->angle - DR * 30;
	// log_val(data, "ray_casting", 'A');
	// fprintf(stderr, "ra: %f\n", ra);
	while (i < 30)
	{
		// fprintf(stderr, "TESTING1\n");
		dof = 0;
		float aTan = -1 / tan(ra); // calculates the x and y components of the ray direction vector based on the pixel coordinates on the screen
		// fprintf(stderr, "aTan: %f\n", aTan);
		if (ra > PI) // ? looking up
		{
			// fprintf(stderr, "ra > PI\n");
			ray_y = (((int)data->file_data->player->y >> 6) << 6) - 0.0001;
			ray_x = (data->file_data->player->y - ray_y) * aTan + data->file_data->player->x;
			off_y = -64;
			off_x = -off_y * aTan;
		}
		if (ra < PI) // ? looking down
		{
			// fprintf(stderr, "ra < PI\n");
			ray_y = (((int)data->file_data->player->y >> 6) << 6) + 64;
			ray_x = (data->file_data->player->y - ray_y) * aTan + data->file_data->player->x;
			off_y = 64;
			off_x = -off_y * aTan;
		}
		if (ra == 0 || ra == PI) // ? looking left or right
		{
			// fprintf(stderr, "ra = 0 || ra = PI\n");
			ray_x = data->file_data->player->x;
			ray_y = data->file_data->player->y;
			dof = 8;
		}
		while (dof < 8)
		{
			// fprintf(stderr, "TESTING5\n");
			int mapX = (int)(ray_x) >> 6;
			// fprintf(stderr, "mapX: %d\n", mapX);
			int mapY = (int)(ray_y) >> 6;
			// fprintf(stderr, "mapY: %d\n", mapY);
			int mapPosition = mapY * data->file_data->map_data->col + mapX;
			// fprintf(stderr, "mapPosition: %d\n", mapPosition);
			// fprintf(stderr, "mapData: %s\n", data->file_data->map_data->copy[mapPosition]);
			if (mapPosition < mapX * mapY && data->file_data->map_data->copy[mapY][mapX] == '1')
			{
				// fprintf(stderr, "TESTING6\n");
				dof = 8;
			}
			else
			{
				// fprintf(stderr, "TESTING7\n");
				ray_x += off_x;
				ray_y += off_y;
				dof += 1;
			}
		}
		i++;
		ra+=DR;
		draw_ray(data, ra, ray_x, ray_y, off_x, off_y);
	}
}

// bool test_ray(t_general_data *data)
// {
// 	int ray, mx, my, mp, dof;
// 	float rx, ry, ra, xo, yo;
// 	ra = data->p.pa;
// 	for (ray = 0; ray < 1; ray++)
// 	{
// 		//--Check horizontal lines--
// 		dof = 0;
// 		float aTan = -1 / tan(ra);
// 		// first checking if the ray is looking up or down (PI = 180degree)
// 		if (ra > M_PI) // looking down
// 		{
// 			ry = (((int)data->p.py * data->map->ratio) / data->map->ratio) - 0.0001; // maybe presicion can go?
// 			rx = (data->p.py - ry) * aTan + data->p.px;
// 			yo = data->map->ratio * -1;
// 			xo = data->map->ratio * aTan;
// 		}
// 		if (ra < M_PI) // looking up
// 		{
// 			ry = (((int)data->p.py * data->map->ratio) / data->map->ratio) + data->map->ratio;
// 			rx = (data->p.py - ry) * aTan + data->p.px;
// 			yo = data->map->ratio;
// 			xo = data->map->ratio * -1 * aTan;
// 		}
// 		if (ra == 0 || ra == M_PI) // if the ray is looking direct rigt or left it is impossible to hit horizontal line
// 		{
// 			rx = data->p.px;
// 			ry = data->p.py;
// 			dof = 8; // we wont check forever just first eight
// 		}
// 		while (dof < 8)
// 		{
// 			mx = (int)(rx) >> 6;
// 			my = (int)(ry) >> 6;
// 			mp = my * data->map->row + mx;
// 			// if(mp < data->map->row * data->map->col && data->map->map_data[(int)mp] == '1') //hit wall
// 			// 	dof = 8;
// 			// else //next line
// 			// {
// 			rx += xo;
// 			ry += yo;
// 			dof++;
// 			// }
// 		}
// 	}
// }