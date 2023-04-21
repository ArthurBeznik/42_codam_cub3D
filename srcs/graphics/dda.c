#include <graphics.h>

bool dda(t_general_data *data)
{
	t_dda *dda;

	dda = data->graphics->dda;

	// bool is_done = false;

	// fprintf(stderr, "pos_x | pos_y : %f | %f\n", dda->pos_x, dda->pos_y); // ? testing

	// fprintf(stderr, "w | h : %d | %d\n", w, h); // ? testing

	/* raycasting loop: goes through every x until reaching map width */
	for (int x = 0; x < dda->w; x++)
	{
		/* calculate ray position and direction */
		dda->camera_x = 2 * x / (double)dda->w - 1;					// x-coordinate in camera space
		dda->ray_dir_x = dda->dir_x + dda->plane_x * dda->camera_x; // ray starts at player position
		dda->ray_dir_y = dda->dir_y + dda->plane_y * dda->camera_x; // ray starts at player position

		// fprintf(stderr, "ray_dir_x | ray_dir_y : %f | %f\n", dda->ray_dir_x, dda->ray_dir_y); // ? testing
		// fprintf(stderr, "camera_x : %f\n", dda->camera_x); // ? testing

		/* square of the map the ray is in */
		dda->map_x = (int)dda->pos_x;
		dda->map_y = (int)dda->pos_y;

		// fprintf(stderr, "dda->map_x | dda->map_y : %d | %d\n", dda->map_x, dda->map_y); // ? testing
		// fprintf(stderr, "dda->pos_x | dda->pos_y : %f | %f\n", dda->pos_x, dda->pos_y); // ? testing

		/* length of ray from one x or y-side to next x or y-side */
		dda->delta_dist_x = (dda->ray_dir_x == 0) ? 1e30 : fabs(1 / dda->ray_dir_x);
		dda->delta_dist_y = (dda->ray_dir_y == 0) ? 1e30 : fabs(1 / dda->ray_dir_y);
		// fprintf(stderr, "delta_dist_x | delta_dist_y : %f | %f\n", dda->delta_dist_x, dda->delta_dist_y); // ? testing

		/**
		 * calculate step and initial side_dist
		 * 	if ray_dir_x 
		 * 		= 1		=> looking west
		 * 		= -1	=> looking east
		 * 	if ray_dir_y 
		 * 		= 1		=> looking south
		 * 		= -1	=> looking north
		*/
		if (dda->ray_dir_x < 0)
		{
			dda->step_x = -1;
			dda->side_dist_x = (dda->pos_x - dda->map_x) * dda->delta_dist_x;
		}
		else
		{
			dda->step_x = 1;
			dda->side_dist_x = (dda->map_x + 1.0 - dda->pos_x) * dda->delta_dist_x;
		}
		if (dda->ray_dir_y < 0)
		{
			dda->step_y = -1;
			dda->side_dist_y = (dda->pos_y - dda->map_y) * dda->delta_dist_y;
		}
		else
		{
			dda->step_y = 1;
			dda->side_dist_y = (dda->map_y + 1.0 - dda->pos_y) * dda->delta_dist_y;
		}
		// fprintf(stderr, "side_dist_x | side_dist_y : %f | %f\n", dda->side_dist_x, dda->side_dist_y); // ? testing

		/* DDA */
		int hit = 0;
		while (hit == 0)
		{
			/* jump to next map square, either in x-direction, or in y-direction, the closest */
			if (dda->side_dist_x < dda->side_dist_y)
			{
				dda->side_dist_x += dda->delta_dist_x;
				dda->map_x += dda->step_x;
				if (dda->step_x == -1)
					dda->side = WEST;
				if (dda->step_x == 1)
					dda->side = EAST;		
			}
			else
			{
				dda->side_dist_y += dda->delta_dist_y;
				dda->map_y += dda->step_y;
				if (dda->step_y == -1)
					dda->side = NORTH;
				if (dda->step_y == 1)
					dda->side = SOUTH;
			}

			// fprintf(stderr, "dda->map_x | dda->map_y | value : %d | %d | %c\n", dda->map_x, dda->map_y, data->file_data->map_data->copy[dda->map_y][dda->map_x]); // ? testing

			/* check if ray has hit a wall */
			if (data->file_data->map_data->copy[dda->map_y][dda->map_x] == '1')
				hit = 1;
		}

		/* calculate distance of the ray to the wall, to avoid fisheye effect */
		if (dda->side == WEST || dda->side == EAST)
			dda->perp_wall_dist = (dda->side_dist_x - dda->delta_dist_x);
		else
			dda->perp_wall_dist = (dda->side_dist_y - dda->delta_dist_y);

		/* calculate height of line to draw on screen */
		int line_height = (int)(dda->h / dda->perp_wall_dist);

		/**
		 * calculate lowest and highest pixel to fill in current stripe
		 * 	here we draw from the center of the screen (i.e. / 2)
		 * 	if the other points are outside of the screen, they are capped to 0 to h-1
		 */
		int draw_start = -line_height / 2 + dda->h / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + dda->h / 2;
		if (draw_end >= dda->h)
			draw_end = dda->h - 1;

		/* choose wall color */
		int color;
		switch (dda->side)
		{
			case NORTH:
				color = GREEN;
				break;
			case WEST:
				color = YELLOW;
				break;
			case SOUTH:
				color = RED;
				break;
			case EAST:
				color = BLUE;
				break;
		}

		/* draw the pixels of the stripe as a vertical line */
		int n = 0;
		int y = draw_start;
		// fprintf(stderr, "start | end | height : %d | %d | %d\n", drawStart, drawEnd, lineHeight);
		while (n < (draw_end - draw_start))
		{
			mlx_put_pixel(data->graphics->img_3d, x, y + n, color);
			n++;
		}
		// fprintf(stderr, "here\n"); // ? testing
	}
	return (true);
}
