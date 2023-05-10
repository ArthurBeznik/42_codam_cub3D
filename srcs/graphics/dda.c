#include <cub3D.h>

unsigned int	reverse_bits(unsigned int num)
{
	unsigned int	nb_bits;
	unsigned int	rev_num;
	unsigned int	i;

	nb_bits = sizeof(num) * 8;
	rev_num = 0;
	i = 0;
	while (i < nb_bits)
	{
		if ((num & (1 << i)))
			rev_num |= 1 << ((nb_bits - 1) - i);
		i++;
	}
	return (rev_num);
}

void	put_multi_pixels(mlx_image_t *img, unsigned int color, \
	int pixels, int offset)
{
	uint32_t	*px;
	int			i;

	px = (uint32_t *)img->pixels;
	i = 0;
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

	r = texture->pixels[y * texture->width * 4 + (x * 4)];
	g = texture->pixels[y * texture->width * 4 + (x * 4) + 1];
	b = texture->pixels[y * texture->width * 4 + (x * 4) + 2];
	a = texture->pixels[y * texture->width * 4 + (x * 4) + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * starting texture coordinate
 * cast the texture coordinate to integer, 
 * 		and mask with (tex_height - 1) in case of overflow
 */
void	cast_textures(t_general_data *data, int x)
{
	int	y;

	data->graphics.calc.tex_pos = (data->graphics.calc.draw_start \
		- data->graphics.calc.pitch - data->graphics.dda.h / 2 \
		+ data->graphics.calc.line_height / 2) * data->graphics.calc.step;
	y = data->graphics.calc.draw_start;
	while (y < data->graphics.calc.draw_end)
	{
		data->graphics.calc.tex_y = (int)data->graphics.calc.tex_pos \
			& (PIXELS - 1);
		data->graphics.calc.tex_pos += data->graphics.calc.step;
		if (data->graphics.dda.side == NORTH)
			data->graphics.textures.rgba = \
				get_rgba(data->graphics.textures.north_tex, \
				data->graphics.calc.tex_x, data->graphics.calc.tex_y);
		if (data->graphics.dda.side == WEST)
			data->graphics.textures.rgba = \
				get_rgba(data->graphics.textures.west_tex, \
				data->graphics.calc.tex_x, data->graphics.calc.tex_y);
		if (data->graphics.dda.side == SOUTH)
			data->graphics.textures.rgba = \
				get_rgba(data->graphics.textures.south_tex, \
				data->graphics.calc.tex_x, data->graphics.calc.tex_y);
		if (data->graphics.dda.side == EAST)
			data->graphics.textures.rgba = \
				get_rgba(data->graphics.textures.east_tex, \
				data->graphics.calc.tex_x, data->graphics.calc.tex_y);
		mlx_put_pixel(data->graphics.img_3d, x, y, \
			data->graphics.textures.rgba);
		y++;
	}
}

/**
 * calculate value of wall_x
 * x coordinate on the texture
 * how much to increase the texture coordinate per screen pixel
 */
void	calc_value_wall_texture(t_general_data *data)
{
	if (data->graphics.dda.side == WEST || data->graphics.dda.side == EAST)
		data->graphics.calc.wall_x = data->graphics.dda.pos_y \
			+ data->graphics.dda.perp_wall_dist * data->graphics.dda.ray_dir_y;
	else
		data->graphics.calc.wall_x = data->graphics.dda.pos_x \
			+ data->graphics.dda.perp_wall_dist * data->graphics.dda.ray_dir_x;
	data->graphics.calc.wall_x -= floor((data->graphics.calc.wall_x));
	data->graphics.calc.tex_x = (int)(data->graphics.calc.wall_x \
		* (double)(PIXELS));
	if (data->graphics.dda.side == EAST)
		data->graphics.calc.tex_x = PIXELS - data->graphics.calc.tex_x - 1;
	if (data->graphics.dda.side == NORTH)
		data->graphics.calc.tex_x = PIXELS - data->graphics.calc.tex_x - 1;
	data->graphics.calc.step = 1.0 * PIXELS / data->graphics.calc.line_height;
}

/**
 * calculate distance of the ray to the wall, to avoid fisheye effect
 * calculate height of line to draw on screen
 * calculate lowest and highest pixel to fill in current stripe
 * here we draw from the center of the screen (i.e. / 2)
 * if the other points are outside of the screen, they are capped to 0 to h-1
 */
void	calc_wall_dist_height(t_general_data *data)
{
	if (data->graphics.dda.side == WEST || data->graphics.dda.side == EAST)
		data->graphics.dda.perp_wall_dist = (data->graphics.dda.side_dist_x \
			- data->graphics.dda.delta_dist_x);
	else
		data->graphics.dda.perp_wall_dist = (data->graphics.dda.side_dist_y \
			- data->graphics.dda.delta_dist_y);
	data->graphics.calc.line_height = (int)(data->graphics.dda.h \
		/ data->graphics.dda.perp_wall_dist);
	data->graphics.calc.pitch = 100;
	data->graphics.calc.draw_start = -data->graphics.calc.line_height \
		/ 2 + data->graphics.dda.h / 2 + data->graphics.calc.pitch;
	if (data->graphics.calc.draw_start < 0)
		data->graphics.calc.draw_start = 0;
	data->graphics.calc.draw_end = data->graphics.calc.line_height \
		/ 2 + data->graphics.dda.h / 2 + data->graphics.calc.pitch;
	if (data->graphics.calc.draw_end >= data->graphics.dda.h)
		data->graphics.calc.draw_end = data->graphics.dda.h - 1;
}

/**
 * jump to next map square, either in x-direction, or in y-direction, the closest
 * check if ray has hit a wall
 */
void	perform_dda(t_general_data *data)
{
	int	x;
	int	y;

	data->graphics.calc.hit = 0;
	while (data->graphics.calc.hit == 0)
	{
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
		x = data->graphics.dda.map_x;
		y = data->graphics.dda.map_y;
		if (data->file_data.map_data.copy[y][x] == '1')
			data->graphics.calc.hit = 1;
	}
}

/**
 * calculate step and initial side_dist
 * 	if ray_dir_x
 * 		= 1		=> looking west
 * 		= -1	=> looking east
 * 	if ray_dir_y
 * 		= 1		=> looking south
 * 		= -1	=> looking north
 */
void	calc_step_side_dist(t_general_data *data)
{
	if (data->graphics.dda.ray_dir_x < 0)
	{
		data->graphics.dda.step_x = -1;
		data->graphics.dda.side_dist_x = (data->graphics.dda.pos_x \
			- data->graphics.dda.map_x) * data->graphics.dda.delta_dist_x;
	}
	else
	{
		data->graphics.dda.step_x = 1;
		data->graphics.dda.side_dist_x = (data->graphics.dda.map_x + 1.0 \
			- data->graphics.dda.pos_x) * data->graphics.dda.delta_dist_x;
	}
	if (data->graphics.dda.ray_dir_y < 0)
	{
		data->graphics.dda.step_y = -1;
		data->graphics.dda.side_dist_y = (data->graphics.dda.pos_y \
			- data->graphics.dda.map_y) * data->graphics.dda.delta_dist_y;
	}
	else
	{
		data->graphics.dda.step_y = 1;
		data->graphics.dda.side_dist_y = (data->graphics.dda.map_y \
			+ 1.0 - data->graphics.dda.pos_y) * data->graphics.dda.delta_dist_y;
	}
}

/**
 * calculate ray position and direction
 * square of the map the ray is in
 * length of ray from one x or y-side to next x or y-side
 */
void	calc_direction_camera(t_general_data *data, int x)
{
	data->graphics.dda.camera_x = 2 * x / (double)data->graphics.dda.w - 1;
	data->graphics.dda.ray_dir_x = data->graphics.dda.dir_x \
		+ data->graphics.dda.plane_x * data->graphics.dda.camera_x;
	data->graphics.dda.ray_dir_y = data->graphics.dda.dir_y \
		+ data->graphics.dda.plane_y * data->graphics.dda.camera_x;
	data->graphics.dda.map_x = (int)data->graphics.dda.pos_x;
	data->graphics.dda.map_y = (int)data->graphics.dda.pos_y;
	if (data->graphics.dda.ray_dir_x == 0)
		data->graphics.dda.delta_dist_x = 1e30;
	else
		data->graphics.dda.delta_dist_x = \
			fabs(1 / data->graphics.dda.ray_dir_x);
	if (data->graphics.dda.ray_dir_y == 0)
		data->graphics.dda.delta_dist_y = 1e30;
	else
		data->graphics.dda.delta_dist_y = \
			fabs(1 / data->graphics.dda.ray_dir_y);
}

/**
 * raycasting loop: goes through every x until reaching map width
 */
bool	dda(t_general_data *data)
{
	int	x;

	put_multi_pixels(data->graphics.img_3d, \
		reverse_bits(data->file_data.identifiers.ceiling.rgba), \
		((data->graphics.dda.h / 3 * 2) * data->graphics.dda.w), 0);
	put_multi_pixels(data->graphics.img_3d, \
		reverse_bits(data->file_data.identifiers.floor.rgba), \
		(data->graphics.dda.h / 3 * data->graphics.dda.w), \
		((data->graphics.dda.h / 3 * 2) * data->graphics.dda.w));
	x = 0;
	while (x < data->graphics.dda.w)
	{
		calc_direction_camera(data, x);
		calc_step_side_dist(data);
		perform_dda(data);
		calc_wall_dist_height(data);
		calc_value_wall_texture(data);
		cast_textures(data, x);
		x++;
	}
	return (true);
}
