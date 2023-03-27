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
		if (!check_put_pixel(data, x1, y1))
			return (false);
		// mlx_put_pixel(data->graphics->img, x1, y1, 0xFF0000FF);
		mlx_put_pixel(data->graphics->img, ray_x, ray_y, 0xFF0000FF);
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
	int	hit_x;
	int	hit_y;

	i = 0;
	ra = data->file_data->player->angle;
	// ra = data->file_data->player->angle - DR * 30;
	// log_val(data, "ray_casting", 'A');
	// fprintf(stderr, "ra: %f\n", ra);
	while (i < 1)
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
		fprintf(stderr, "col | row : %d | %d\n", data->file_data->map_data->col, data->file_data->map_data->row);
		while (dof < 8)
		{
			// fprintf(stderr, "TESTING5\n");
			hit_x = (int)(ray_x) >> 6; // ? x where the ray hits a wall or line
			// fprintf(stderr, "mapX: %d\n", mapX);
			hit_y = (int)(ray_y) >> 6; // ? y where the ray hits a wall or line
			// fprintf(stderr, "dof: %d\n", dof);
			// fprintf(stderr, "mapY: %d\n", mapY);
			// fprintf(stderr, "mapPosition: %d\n", mapPosition);
			fprintf(stderr, "hit_x | hit_y (value) : %d | %d (%c)\n", hit_x, hit_y, data->file_data->map_data->copy[hit_y][hit_x]);
			// if ((hit_x > data->file_data->map_data->row || hit_y > data->file_data->map_data->col) && data->file_data->map_data->copy[hit_y][hit_x] == '1')
			if ((hit_x >= 0 && hit_y >= 0) \
				&& ((hit_x < data->file_data->map_data->row && hit_y < data->file_data->map_data->col)) \
				&& data->file_data->map_data->copy[hit_y][hit_x] == '1')
			{
				fprintf(stderr, "\thit wall\n");
				dof = 8;
			}
			else
			{
				fprintf(stderr, "\tdid not hit\n");
				ray_x += off_x;
				ray_y += off_y;
				dof += 1;
				fprintf(stderr, "rx | ry : %d | %d\n", ray_x, ray_y);
			}
		}
		i++;
		// ra+=DR;
		draw_ray(data, ra, ray_x, ray_y, off_x, off_y);
	}
}