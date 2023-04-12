#include <graphics.h>

void	try_hit_walls(t_general_data *data, t_ray *raymond, float angle, int dof, t_axis axis, t_textures *textures)
{
	while (dof < 8)
	{
		// fprintf(stderr, "dof < 8\n"); // ? testing
		// fprintf(stderr, "x | y : %f | %f\n", round(x), round(y)); // ? testing
		// fprintf(stderr, "dof : %d\n", dof); // ? testing
		raymond->hit_x = (int)(raymond->x) >> 6; // ? x where the ray hits a wall or line
		raymond->hit_y = (int)(raymond->y) >> 6; // where the ray hits a wall or line

		// mp = my * mapX + mx; // !

		// fprintf(stderr, "hit_x | hit_y : %d | %d\n", raymond->hit_x, raymond->hit_y); // ? testing
		// int mp = data->file_data->map_data->copy[raymond->hit_y][raymond->hit_x]; // !
		// fprintf(stderr, "%d\n", mp); // !

		// fprintf(stderr, "col | row : %lld | %lld\n", data->file_data->map_data->col, data->file_data->map_data->row); // ? testing
		
		// if (mp > 0 && mp < mapX * mapY && mapW[mp] > 0) // !
		
		if ((raymond->hit_x >= 0 && raymond->hit_y >= 0) && ((raymond->hit_x < data->file_data->map_data->row && raymond->hit_y < data->file_data->map_data->col)) && data->file_data->map_data->copy[raymond->hit_y][raymond->hit_x] == '1')
		{
			// fprintf(stderr, "hit_x | hit_y (value) : %d | %d (%c)\n", hit_x, hit_y, data->file_data->map_data->copy[hit_y][hit_x]); // ? testing
			// fprintf(stderr, "\thit wall\n"); // ? testing

			// int mp = data->file_data->map_data->copy[raymond->hit_y][raymond->hit_x]; // !
			// fprintf(stderr, "%d\n", mp); // !
			// fprintf(stderr, "raymond angle: %f\n", raymond->angle);
			// fprintf(stderr, "player angle: %f\n", data->file_data->player->angle);
			// fprintf(stderr, "hit angle: %f\n", angle); // ? testing
			dof = 8;
			if (axis == VERTICAL)
			{
				// textures->vmt = mapW[mp] - 1; // !
				if (raymond->angle > M_PI / 4 && raymond->angle < 3 * M_PI / 4) // ! facing north
				{
					// fprintf(stderr, "NORTH\n"); // ? [2pi, pi]
					textures->vmt = 0; // !
					textures->color = RED;
				}
				if (raymond->angle > 5 * M_PI / 4 && raymond->angle < 7 * M_PI / 4) // ! facing south
				{
					// fprintf(stderr, "SOUTH\n"); // ?  [pi, 2pi]
					textures->vmt = 1; // !
					textures->color = GREEN;
				}
				raymond->dist_v = cos(angle) * (raymond->x - data->file_data->player->x) - sin(angle) * (raymond->y - data->file_data->player->y);
			}
			if (axis == HORIZONTAL)
			{
				if (raymond->angle > 3 * M_PI / 4 && raymond->angle < 5 * M_PI / 4) // ! facing west
				{	
					// fprintf(stderr, "WEST\n"); // ? [pi/2, 3pi/2]
					textures->hmt = 2; // !
					textures->color = BLUE;
				}
				if ((raymond->angle > 7 * M_PI / 4 && raymond->angle < (2 * M_PI)) \
					|| (raymond->angle > 0 && raymond->angle < M_PI / 4)) // ! facing east
				{
					// fprintf(stderr, "EAST\n"); // ? [3pi/2, pi/2]
					textures->hmt = 3; // !
					textures->color = YELLOW;
				}
				// textures->hmt = mapW[mp] - 1; // !
				raymond->dist_h = cos(angle) * (raymond->x - data->file_data->player->x) - sin(angle) * (raymond->y - data->file_data->player->y);
			}
			// fprintf(stderr, "dist_h : %f\n", dist_h); // ? testing
		}
		else
		{
			// fprintf(stderr, "\tdid not hit\n"); // ? testing
			raymond->x += raymond->off_x;
			raymond->y += raymond->off_y;
			if (raymond->y < 0 || raymond->x < 0 || raymond->x > data->graphics->width || raymond->y > data->graphics->height)
			{
				// fprintf(stderr, "Negative rx or ry, stopping\n"); // ? testing
				dof = 8;
			}
			dof += 1;
			// fprintf(stderr, "rx | ry : %d | %d\n", x, y); // ? testing
		}
	}
}

void	horizontal_looking(t_general_data *data, t_ray *raymond, float angle, float tan_var)
{
	raymond->dof = 0;
	if (sin(angle) > 0.001) // ? (angle > M_PI) => looking up
	{
		// fprintf(stderr, "angle > M_PI\n"); // ? testing
		raymond->y = (((int)data->file_data->player->y >> 6) << 6) - 0.0001;
		raymond->x = (data->file_data->player->y - raymond->y) * tan_var + data->file_data->player->x;
		raymond->off_y = -64;
		raymond->off_x = -raymond->off_y * tan_var;
	}
	else if (sin(angle) < -0.001) // ? (angle < M_PI) => looking down
	{
		// fprintf(stderr, "angle < M_PI\n"); // ? testing
		raymond->y = (((int)data->file_data->player->y >> 6) << 6) + 64;
		raymond->x = (data->file_data->player->y - raymond->y) * tan_var + data->file_data->player->x;
		raymond->off_y = 64;
		raymond->off_x = -raymond->off_y * tan_var;
	}
	else // ? (angle == 0 || angle == M_PI) => looking left or right
	{
		// fprintf(stderr, "H - left right => no hit on horizontal\n"); // ? testing
		raymond->x = data->file_data->player->x;
		raymond->y = data->file_data->player->y;
		raymond->dof = 8;
	}
}

void	vertical_looking(t_general_data *data, t_ray *raymond, float angle, float tan_var)
{
	raymond->dof = 0;
	if (cos(angle) > 0.001) // ? (angle > M_PI) => looking left
	{
		// fprintf(stderr, "angle > M_PI\n"); // ? testing
		// fprintf(stderr, "before rx | ry : %f | %f\n", x, y); // ? testing
		// log_val(data, "ray_caster", 'P'); // ? testing
		raymond->x = (((int)data->file_data->player->x >> 6) << 6) + 64;
		raymond->y = (data->file_data->player->x - raymond->x) * tan_var + data->file_data->player->y;
		raymond->off_x = 64;
		raymond->off_y = -raymond->off_x * tan_var;
		// fprintf(stderr, "after rx | ry : %f | %f\n", x, y); // ? testing
		// fprintf(stderr, "off_x | off_y : %f | %f\n", raymond->off_x, raymond->off_y); // ? testing
	}
	else if (cos(angle) < -0.001) // ? (angle < M_PI) => looking right
	{
		// fprintf(stderr, "angle < M_PI\n"); // ? testing
		// fprintf(stderr, "before rx | ry : %f | %f\n", x, y); // ? testing
		raymond->x = (((int)data->file_data->player->x >> 6) << 6) - 0.0001;
		raymond->y = (data->file_data->player->x - raymond->x) * tan_var + data->file_data->player->y;
		raymond->off_x = -64;
		raymond->off_y = -raymond->off_x * tan_var;
		// fprintf(stderr, "after rx | ry : %f | %f\n", x, y); // ? testing
		// fprintf(stderr, "off_x | off_y : %f | %f\n", raymond->off_x, raymond->off_y); // ? testing
	}
	else // ? (angle == 0 || angle == M_PI) => looking up or down
	{
		// fprintf(stderr, "V - up down => no hit on vertical\n"); // ? testing
		raymond->x = data->file_data->player->x;
		raymond->y = data->file_data->player->y;
		raymond->dof = 8;
		// fprintf(stderr, "rx | ry : %f | %f\n", x, y); // ? testing
	}
}

void	vertical_ray(t_general_data *data, t_ray *raymond, float angle, t_textures *textures)
{
	int		dof;
	float	tan_var;

	raymond->angle = angle;
	// fprintf(stderr, "angle | raymond angle : %f | %f\n", angle, raymond->angle); // ? testing
	// fprintf(stderr, "raymond angle: %f", raymond->angle); // ? testing
	dof = 0;
	raymond->dist_v = 100000;
	tan_var = tan(angle);
	raymond->tan_var = tan_var;
	// log_val(data, "ray_caster", 'A'); // ? testing
	// log_val(data, "ray_caster", 'P'); // ? testing
	vertical_looking(data, raymond, angle, tan_var);
	dof = raymond->dof;
	try_hit_walls(data, raymond, angle, dof, VERTICAL, textures);
}

void	horizontal_ray(t_general_data *data, t_ray *raymond, float angle, t_textures *textures)
{
	int		dof;
	float	tan_var;

	// fprintf(stderr, "angle: %f\n", angle);
	// if (angle > 2 * M_PI)
	// 	angle -= RESET_ANGLE;
	// if (angle < 0)
	// 	angle += RESET_ANGLE;
	// fprintf(stderr, "angle: %f\n", angle);
	raymond->vx = raymond->x;
	raymond->vy = raymond->y;
	// fprintf(stderr, "rx | ry : %f | %f\n", raymond->x, raymond->y); // ? testing
	dof = 0;
	raymond->dist_h = 100000;
	tan_var = 1.0 / raymond->tan_var;
	raymond->tan_var = tan_var;
	// fprintf(stderr, "tan: %f\n", tan_var); // ? testomg
	horizontal_looking(data, raymond, angle, tan_var);
	dof = raymond->dof;
	// fprintf(stderr, "col | row : %d | %d\n", data->file_data->map_data->col, data->file_data->map_data->row); // ? testing
	try_hit_walls(data, raymond, angle, dof, HORIZONTAL, textures);

	textures->shade = 1; // !
	if (raymond->dist_v < raymond->dist_h)
	{
		textures->hmt = textures->vmt; // !
		textures->shade = 0.5; // !
		raymond->x = raymond->vx;
		raymond->y = raymond->vy;
		raymond->dist_h = raymond->dist_v;
	}
	// ! horizontal hits first
}
