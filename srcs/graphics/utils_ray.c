#include <graphics.h>

void	try_hit_walls(t_general_data *data, t_ray *raymond, float angle, int dof, t_axis axis, t_textures *textures)
{
	while (dof < 8)
	{
		// fprintf(stderr, "x | y : %f | %f\n", round(x), round(y)); // ? testing
		// fprintf(stderr, "dof : %d\n", dof); // ? testing
		raymond->hit_x = (int)(raymond->x) >> 6; // ? x where the ray hits a wall or line
		raymond->hit_y = (int)(raymond->y) >> 6; // where the ray hits a wall or line
		bool collision = false;


		// fprintf(stderr, "hit_x | hit_y : %d | %d\n", raymond->hit_x, raymond->hit_y); // ? testing
		// fprintf(stderr, "col | row : %lld | %lld\n", data->file_data->map_data->col, data->file_data->map_data->row); // ? testing
		
		if ((raymond->hit_x >= 0 && raymond->hit_y >= 0) && ((raymond->hit_x < data->file_data->map_data->row \
			&& raymond->hit_y < data->file_data->map_data->col)) && \
			data->file_data->map_data->copy[(int)raymond->hit_y][(int)raymond->hit_x] == '1')
		{
			collision = true;
			// fprintf(stderr, "hit_x | hit_y (value) : %d | %d (%c)\n", raymond->hit_x, raymond->hit_y, data->file_data->map_data->copy[raymond->hit_y][raymond->hit_x]); // ? testing
			// fprintf(stderr, "raymond angle: %f\n", raymond->angle);
			// fprintf(stderr, "player angle: %f\n", data->file_data->player->angle);
			// fprintf(stderr, "hit angle: %f\n", angle); // ? testing
			dof = 8;
			// fprintf(stderr, "Angle is %f\n", angle);
			
			if (axis == VERTICAL)
			{
				// textures->vmt = 1;
				// textures->vmt = data->file_data->map_data->copy[raymond->hit_y][raymond->hit_x]; // !
				// fprintf(stderr, "vmt : %d\n", textures->vmt);
				// anlge >= 0.785398163397448309615660845819875721 && angle < 2.356194490192344928846982537459627163
				if (raymond->angle >= M_PI_4 && raymond->angle < 3 * M_PI_4) // ! facing north
				{
					// textures->vmt = mapW[mp] - 1; // !
					// fprintf(stderr, "NORTH\n"); // ? [2pi, pi]
					// textures->vmt = 0; // !
				}
				// angle >= 3.926990816987241548078304229099378605 && anle < 5.497787143782138167309625920739130047
				if (raymond->angle >= 5 * M_PI_4 && raymond->angle < 7 * M_PI_4) // ! facing south
				{
					// textures->vmt = mapW[mp] - 1; // !
					// fprintf(stderr, "SOUTH\n"); // ?  [pi, 2pi]
					// textures->vmt = 1; // !
				}
				raymond->dist_v = cos(angle) * (raymond->x - data->file_data->player->x) - sin(angle) * (raymond->y - data->file_data->player->y);
			}
			if (axis == HORIZONTAL)
			{
				// textures->hmt = 2;
				// textures->hmt = data->file_data->map_data->copy[raymond->hit_y][raymond->hit_x]; // !
				// fprintf(stderr, "hmt : %d\n", textures->hmt);
				// anlge >= 2.356194490192344928846982537459627163 && angle < 3.926990816987241548078304229099378605
				if (raymond->angle >= 3 * M_PI_4 && raymond->angle < 5 * M_PI_4) // ! facing west
				{	
					// fprintf(stderr, "WEST\n"); // ? [pi/2, 3pi/2]
					// textures->hmt = 2; // !
				}
				// angle >= 5.497787143782138167309625920739130047 && angle < 6.28318530717958647692528676655900576 
				// || angle > 0 && angle < 0.785398163397448309615660845819875721
				
				// if (raymond->hit_x - (int)raymond->hit_x <= 0.001)
				// 	//either east or west
				// else if (raymond->hit_y - (int)raymond->hit_y <= 0.001)
				// 	//either north or south

				if ((raymond->angle >= 7 * M_PI_4 && raymond->angle < (2 * M_PI)) \
					|| (raymond->angle > 0 && raymond->angle < M_PI_4)) // ! facing east
				{
					// fprintf(stderr, "EAST\n"); // ? [3pi/2, pi/2]
					// textures->hmt = 3; // !
				}
				raymond->dist_h = cos(angle) * (raymond->x - data->file_data->player->x) - sin(angle) * (raymond->y - data->file_data->player->y);
			}
			// (void)axis;

			raymond->hit_x = raymond->x;
			raymond->hit_y = raymond->y;
			bool North = (raymond->y - data->file_data->player->y) < 0;
			bool West = (raymond->x - data->file_data->player->x) < 0;
			float integral = (float)((int)raymond->hit_x);
			// fprintf(stderr, "x integral: %f\n", integral);
			// fprintf(stderr, "x float: %d\n", raymond->hit_x);
			// fprintf(stderr, "raymond x: %f\n", raymond->x);

			//x integral or y integral check
			// bool y

			
			if (collision)
			{
				if (West)
				{
					printf("West\n");
					fprintf(stderr, "x: %d\n", raymond->hit_x);
					fprintf(stderr, "y: %d\n", raymond->hit_y);
					// fprintf(stderr, "%f\n", (raymond->x - data->file_data->player->x));
					// printf("West int: %f, float: %f, diff: %f\n", integral, raymond->x, ((raymond->x - integral)));
					fprintf(stderr, "------------------------------------\n");
				}
				else
				{
					printf("East\n");
					fprintf(stderr, "x: %d\n", raymond->hit_x);
					fprintf(stderr, "y: %d\n", raymond->hit_y);
					// printf("East int: %f, float: %f, diff: %f\n", integral, raymond->x, ((raymond->x - integral)));
					fprintf(stderr, "------------------------------------\n");

				}
				if (North)
				{
					printf("North\n");
					fprintf(stderr, "x: %d\n", raymond->hit_x);
					fprintf(stderr, "y: %d\n", raymond->hit_y);
					fprintf(stderr, "------------------------------------\n");
					// fprintf(stderr, "%f\n", (raymond->y - data->file_data->player->y));
				}
				else
				{
					printf("South\n");
					fprintf(stderr, "x: %d\n", raymond->hit_x);
					fprintf(stderr, "y: %d\n", raymond->hit_y);
					fprintf(stderr, "------------------------------------\n");
				}
				if ((raymond->x - integral)*(raymond->x - integral) >= 0.00000001)
				{
					if (West)
						textures->hmt = 2;
					else //east
						textures->hmt = 3;
				}
				else //if (raymond->hit_y - (int)raymond->hit_y <= 0.001)
				{
					// printf("North or south\n");

					if (North)
						textures->vmt = 0;
					else //south
						textures->vmt = 1;
				}
			}
		}
		else
		{
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
