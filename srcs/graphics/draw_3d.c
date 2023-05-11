#include <cub3D.h>

static void	set_wall_textures(t_general_data *data)
{
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
}

/**
 * Calculate step (how much to increase the texture coordinate per screen pixel)
 * Get the starting texture coordinate and loop on y until reaching end pos.
 */
void	draw_3d(t_general_data *data, int x)
{
	int	y;

	data->graphics.calc.step = 1.0 * PIXELS / data->graphics.calc.line_height;
	data->graphics.calc.tex_pos = (data->graphics.calc.draw_start \
		- data->graphics.calc.pitch - data->graphics.dda.h / 2 \
		+ data->graphics.calc.line_height / 2) * data->graphics.calc.step;
	y = data->graphics.calc.draw_start;
	while (y < data->graphics.calc.draw_end)
	{
		data->graphics.calc.tex_y = (int)data->graphics.calc.tex_pos \
			& (PIXELS - 1);
		data->graphics.calc.tex_pos += data->graphics.calc.step;
		set_wall_textures(data);
		mlx_put_pixel(data->graphics.img_3d, x, y, \
			data->graphics.textures.rgba);
		y++;
	}
}
