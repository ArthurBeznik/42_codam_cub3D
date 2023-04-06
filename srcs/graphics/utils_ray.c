#include <graphics.h>

void	try_hit_walls(t_general_data *data, t_ray *raymond, float angle, int dof, t_axis axis)
{
	while (dof < 8)
	{
		// fprintf(stderr, "dof < 8\n");
		// fprintf(stderr, "x | y : %f | %f\n", round(x), round(y));
		// fprintf(stderr, "dof : %d\n", dof);
		raymond->hit_x = (int)(raymond->x) >> 6; // ? x where the ray hits a wall or line
		raymond->hit_y = (int)(raymond->y) >> 6; // where the ray hits a wall or line
		// fprintf(stderr, "hit_x | hit_y : %d | %d\n", raymond->hit_x, raymond->hit_y);
		// fprintf(stderr, "col | row : %lld | %lld\n", data->file_data->map_data->col, data->file_data->map_data->row);
		if ((raymond->hit_x >= 0 && raymond->hit_y >= 0) && ((raymond->hit_x < data->file_data->map_data->row && raymond->hit_y < data->file_data->map_data->col)) && data->file_data->map_data->copy[raymond->hit_y][raymond->hit_x] == '1')
		{
			// fprintf(stderr, "hit_x | hit_y (value) : %d | %d (%c)\n", hit_x, hit_y, data->file_data->map_data->copy[hit_y][hit_x]);
			// fprintf(stderr, "\thit wall\n");
			dof = 8;
			if (axis == VERTICAL)
				raymond->dist_v = cos(angle) * (raymond->x - data->file_data->player->x) - sin(angle) * (raymond->y - data->file_data->player->y);
			if (axis == HORIZONTAL)
				raymond->dist_h = cos(angle) * (raymond->x - data->file_data->player->x) - sin(angle) * (raymond->y - data->file_data->player->y);
			// fprintf(stderr, "dist_h : %f\n", dist_h);
		}
		else
		{
			// fprintf(stderr, "\tdid not hit\n");
			raymond->x += raymond->off_x;
			raymond->y += raymond->off_y;
			if (raymond->y < 0 || raymond->x < 0 || raymond->x > data->graphics->width || raymond->y > data->graphics->height)
			{
				// fprintf(stderr, "Negative rx or ry, stopping\n");
				dof = 8;
			}
			dof += 1;
			// fprintf(stderr, "rx | ry : %d | %d\n", x, y);
		}
	}
}

void	horizontal_looking(t_general_data *data, t_ray *raymond, float angle, float tan_var)
{
	raymond->dof = 0;
	if (sin(angle) > 0.001) // ? (angle > M_PI) => looking up
	{
		// fprintf(stderr, "angle > M_PI\n");
		raymond->y = (((int)data->file_data->player->y >> 6) << 6) - 0.0001;
		raymond->x = (data->file_data->player->y - raymond->y) * tan_var + data->file_data->player->x;
		raymond->off_y = -64;
		raymond->off_x = -raymond->off_y * tan_var;
	}
	else if (sin(angle) < -0.001) // ? (angle < M_PI) => looking down
	{
		// fprintf(stderr, "angle < M_PI\n");
		raymond->y = (((int)data->file_data->player->y >> 6) << 6) + 64;
		raymond->x = (data->file_data->player->y - raymond->y) * tan_var + data->file_data->player->x;
		raymond->off_y = 64;
		raymond->off_x = -raymond->off_y * tan_var;
	}
	else // ? (angle == 0 || angle == M_PI) => looking left or right
	{
		// fprintf(stderr, "H - left right => no hit on horizontal\n");
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
		// fprintf(stderr, "angle > M_PI\n");
		// fprintf(stderr, "before rx | ry : %f | %f\n", x, y);
		// log_val(data, "ray_caster", 'P');
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
		// fprintf(stderr, "V - up down => no hit on vertical\n");
		raymond->x = data->file_data->player->x;
		raymond->y = data->file_data->player->y;
		raymond->dof = 8;
		// fprintf(stderr, "rx | ry : %f | %f\n", x, y);
	}
}

void	vertical_ray(t_general_data *data, t_ray *raymond, float angle)
{
	int		dof;
	float	tan_var;
	// t_ray **raymond;

	// raymond = data->graphics->ray;
	raymond->angle = angle;
	// fprintf(stderr, "angle | raymond angle : %f | %f\n", angle, raymond->angle);
	// fprintf(stderr, "raymond angle: %f", raymond->angle);
	// fprintf(stderr, "cos(angle) = %f\n", cos(angle));
	// fprintf(stderr, "\tVertical\n");
	dof = 0;
	raymond->dist_v = 100000;
	tan_var = tan(angle);
	raymond->tan_var = tan_var;
	// fprintf(stderr, "aTan: %f\n", aTan);
	// log_val(data, "ray_caster", 'A');
	// log_val(data, "ray_caster", 'P');
	vertical_looking(data, raymond, angle, tan_var);
	dof = raymond->dof;
	try_hit_walls(data, raymond, angle, dof, VERTICAL);
}

void	horizontal_ray(t_general_data *data, t_ray *raymond, float angle)
{
	int		dof;
	float	tan_var;

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
	// fprintf(stderr, "col | row : %d | %d\n", data->file_data->map_data->col, data->file_data->map_data->row);
	try_hit_walls(data, raymond, angle, dof, HORIZONTAL);
}

