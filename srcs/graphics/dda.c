#include <cub3D.h>

unsigned int reverseBits(unsigned int num)
{
    unsigned int NO_OF_BITS = sizeof(num) * 8;
    unsigned int reverse_num = 0;
    unsigned int i;
    for (i = 0; i < NO_OF_BITS; i++) {
        if ((num & (1 << i)))
            reverse_num |= 1 << ((NO_OF_BITS - 1) - i);
    }
    return reverse_num;
}

void    put_multi_pixels(mlx_image_t *img, unsigned color, int pixels, int offset)
{
    uint32_t        *px;

    px = (uint32_t *) img->pixels;
    int i = 0;
    while (i < pixels)
    {
        px[offset + i] = color;
        i++;
    }
}

static int	get_rgba(mlx_texture_t *texture, int x, int y)
{
	int	r;
	int	g;
	int	b;
	int	a;

	// fprintf(stderr, "x | y : %d | %d\n", x, y); // ? testing
	r = texture->pixels[y * texture->width * 4 + (x * 4)];
	g = texture->pixels[y * texture->width * 4 + (x * 4) + 1];
	b = texture->pixels[y * texture->width * 4 + (x * 4) + 2];
	a = texture->pixels[y * texture->width * 4 + (x * 4) + 3];
	// fprintf(stderr, "r: %d | g: %d | b: %d | a: %d\n", r,g , b, a); // ? testing
	return (r << 24 | g << 16 | b << 8 | a);
}

bool dda(t_general_data *data)
{
	int		height;
	int		switch_height;
	int 	width;
	int 	line_height;
	int		pitch;
	int		draw_start;
	int		draw_end;
	int		hit;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;

	// fprintf(stderr, "pos_x | pos_y : %f | %f\n", data->graphics.dda.pos_x, data->graphics.dda.pos_y); // ? testing
	// fprintf(stderr, "w | h : %d | %d\n", w, h); // ? testing

	
	height = data->graphics.img->height;
	switch_height = height / 2;
	width = data->graphics.img->width;

	/* fill top half of screen with ceiling color */
	put_multi_pixels(data->graphics.img_3d, reverseBits(data->file_data.identifiers.ceiling.rgba), ((data->graphics.dda.h / 3 * 2) * data->graphics.dda.w), 0);
	// ft_memset(data->graphics.img_3d->pixels, data->file_data.identifiers.ceiling.rgba, switch_height * \
    //         width * sizeof(int));

	/* fill bottom half of screen with floor color */
    put_multi_pixels(data->graphics.img_3d, reverseBits(data->file_data.identifiers.floor.rgba), (data->graphics.dda.h / 3 * data->graphics.dda.w), ((data->graphics.dda.h / 3 * 2) * data->graphics.dda.w));
	// ft_memset(data->graphics.img_3d->pixels + switch_height * width, data->file_data.identifiers.floor.rgba, \
    //         (height - switch_height) * width * sizeof(int));

	/* raycasting loop: goes through every x until reaching map width */
	for (int x = 0; x < data->graphics.dda.w; x++)
	{
		/* calculate ray position and direction */
		data->graphics.dda.camera_x = 2 * x / (double)data->graphics.dda.w - 1;					// x-coordinate in camera space
		data->graphics.dda.ray_dir_x = data->graphics.dda.dir_x + data->graphics.dda.plane_x * data->graphics.dda.camera_x; // ray starts at player position
		data->graphics.dda.ray_dir_y = data->graphics.dda.dir_y + data->graphics.dda.plane_y * data->graphics.dda.camera_x; // ray starts at player position

		// fprintf(stderr, "camera_x : %f\n", data->graphics.dda.camera_x); // ? testing
		// fprintf(stderr, "ray_dir_x | ray_dir_y : %f | %f\n", data->graphics.dda.ray_dir_x, data->graphics.dda.ray_dir_y); // ? testing

		/* square of the map the ray is in */
		data->graphics.dda.map_x = (int)data->graphics.dda.pos_x;
		data->graphics.dda.map_y = (int)data->graphics.dda.pos_y;

		// fprintf(stderr, "data->graphics.dda.map_x | data->graphics.dda.map_y : %d | %d\n", data->graphics.dda.map_x, data->graphics.dda.map_y); // ? testing
		// fprintf(stderr, "data->graphics.dda.pos_x | data->graphics.dda.pos_y : %f | %f\n", data->graphics.dda.pos_x, data->graphics.dda.pos_y); // ? testing

		/* length of ray from one x or y-side to next x or y-side */
		data->graphics.dda.delta_dist_x = (data->graphics.dda.ray_dir_x == 0) ? 1e30 : fabs(1 / data->graphics.dda.ray_dir_x);
		data->graphics.dda.delta_dist_y = (data->graphics.dda.ray_dir_y == 0) ? 1e30 : fabs(1 / data->graphics.dda.ray_dir_y);
		// fprintf(stderr, "delta_dist_x | delta_dist_y : %f | %f\n", data->graphics.dda.delta_dist_x, data->graphics.dda.delta_dist_y); // ? testing

		/**
		 * calculate step and initial side_dist
		 * 	if ray_dir_x 
		 * 		= 1		=> looking west
		 * 		= -1	=> looking east
		 * 	if ray_dir_y 
		 * 		= 1		=> looking south
		 * 		= -1	=> looking north
		*/
		if (data->graphics.dda.ray_dir_x < 0)
		{
			data->graphics.dda.step_x = -1;
			data->graphics.dda.side_dist_x = (data->graphics.dda.pos_x - data->graphics.dda.map_x) * data->graphics.dda.delta_dist_x;
		}
		else
		{
			data->graphics.dda.step_x = 1;
			data->graphics.dda.side_dist_x = (data->graphics.dda.map_x + 1.0 - data->graphics.dda.pos_x) * data->graphics.dda.delta_dist_x;
		}
		if (data->graphics.dda.ray_dir_y < 0)
		{
			data->graphics.dda.step_y = -1;
			data->graphics.dda.side_dist_y = (data->graphics.dda.pos_y - data->graphics.dda.map_y) * data->graphics.dda.delta_dist_y;
		}
		else
		{
			data->graphics.dda.step_y = 1;
			data->graphics.dda.side_dist_y = (data->graphics.dda.map_y + 1.0 - data->graphics.dda.pos_y) * data->graphics.dda.delta_dist_y;
		}
		// fprintf(stderr, "side_dist_x | side_dist_y : %f | %f\n", data->graphics.dda.side_dist_x, data->graphics.dda.side_dist_y); // ? testing

		/* DDA */
		hit = 0;
		while (hit == 0)
		{
			/* jump to next map square, either in x-direction, or in y-direction, the closest */
			if (data->graphics.dda.side_dist_x < data->graphics.dda.side_dist_y)
			{
				data->graphics.dda.side_dist_x += data->graphics.dda.delta_dist_x;
				data->graphics.dda.map_x += data->graphics.dda.step_x;
				if (data->graphics.dda.step_x == -1)
					data->graphics.dda.side = WEST;
				if (data->graphics.dda.step_x == 1)
					data->graphics.dda.side = EAST;		
			}
			else
			{
				data->graphics.dda.side_dist_y += data->graphics.dda.delta_dist_y;
				data->graphics.dda.map_y += data->graphics.dda.step_y;
				if (data->graphics.dda.step_y == -1)
					data->graphics.dda.side = NORTH;
				if (data->graphics.dda.step_y == 1)
					data->graphics.dda.side = SOUTH;
			}

			// fprintf(stderr, "data->graphics.dda.map_x | data->graphics.dda.map_y | value : %d | %d | %c\n", data->graphics.dda.map_x, data->graphics.dda.map_y, data->file_data.map_data->copy[data->graphics.dda.map_y][data->graphics.dda.map_x]); // ? testing

			/* check if ray has hit a wall */
			if (data->file_data.map_data.copy[data->graphics.dda.map_y][data->graphics.dda.map_x] == '1')
				hit = 1;
		}

		/* calculate distance of the ray to the wall, to avoid fisheye effect */
		if (data->graphics.dda.side == WEST || data->graphics.dda.side == EAST)
			data->graphics.dda.perp_wall_dist = (data->graphics.dda.side_dist_x - data->graphics.dda.delta_dist_x);
		else
			data->graphics.dda.perp_wall_dist = (data->graphics.dda.side_dist_y - data->graphics.dda.delta_dist_y);

		/* calculate height of line to draw on screen */
		line_height = (int)(data->graphics.dda.h / data->graphics.dda.perp_wall_dist);

		pitch = 100;

		/**
		 * calculate lowest and highest pixel to fill in current stripe
		 * 	here we draw from the center of the screen (i.e. / 2)
		 * 	if the other points are outside of the screen, they are capped to 0 to h-1
		 */
		draw_start = -line_height / 2 + data->graphics.dda.h / 2 + pitch;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + data->graphics.dda.h / 2 + pitch;
		if (draw_end >= data->graphics.dda.h)
			draw_end = data->graphics.dda.h - 1;

		/* calculate value of wall_x */
		if (data->graphics.dda.side == WEST || data->graphics.dda.side == EAST)
			wall_x = data->graphics.dda.pos_y + data->graphics.dda.perp_wall_dist * data->graphics.dda.ray_dir_y;
		else
			wall_x = data->graphics.dda.pos_x + data->graphics.dda.perp_wall_dist * data->graphics.dda.ray_dir_x;
		wall_x -= floor((wall_x));

		/* x coordinate on the texture */
		tex_x = (int)(wall_x * (double)(PIXELS));
		if (data->graphics.dda.side == EAST)
			tex_x = PIXELS - tex_x - 1;
		if (data->graphics.dda.side == NORTH)
			tex_x = PIXELS - tex_x - 1;

		/* how much to increase the texture coordinate per screen pixel */
		step = 1.0 * PIXELS / line_height;

		/* starting texture coordinate */
		tex_pos = (draw_start - pitch - data->graphics.dda.h / 2 + line_height / 2) * step;
		for (int y = draw_start; y < draw_end; y++)
		{
			/* cast the texture coordinate to integer, and mask with (tex_height - 1) in case of overflow */
			tex_y = (int)tex_pos & (PIXELS - 1);
			tex_pos += step;
			// Uint32 color = texture[texNum][PIXELS * texY + texX];
			// buffer[y][x] = color;
			switch (data->graphics.dda.side)
			{
				case NORTH:
					data->graphics.textures.rgba = get_rgba(data->graphics.textures.north_tex, tex_x, tex_y);
					break;
				case WEST:
					data->graphics.textures.rgba = get_rgba(data->graphics.textures.west_tex, tex_x, tex_y);
					break;
				case SOUTH:
					data->graphics.textures.rgba = get_rgba(data->graphics.textures.south_tex, tex_x, tex_y);
					break;
				case EAST:
					data->graphics.textures.rgba = get_rgba(data->graphics.textures.east_tex, tex_x, tex_y);
					break;
			}
			mlx_put_pixel(data->graphics.img_3d, x, y, data->graphics.textures.rgba);
		}
	}
	return (true);
}
