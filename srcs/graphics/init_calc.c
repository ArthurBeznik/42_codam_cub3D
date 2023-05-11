#include <cub3D.h>

bool	init_calc(t_general_data *data)
{
	data->graphics.calc.line_height = NA;
	data->graphics.calc.pitch = 100;
	data->graphics.calc.draw_start = NA;
	data->graphics.calc.draw_end = NA;
	data->graphics.calc.hit = NA;
	data->graphics.calc.wall_x = NA;
	data->graphics.calc.tex_x = NA;
	data->graphics.calc.tex_y = NA;
	data->graphics.calc.tex_pos = NA;
	data->graphics.calc.step = NA;
	return (true);
}
