#include <cub3D.h>

static void	init_direction(t_general_data *data, int x, int y)
{
	int	centered;

	centered = PIXELS / 2;
	if (data->file_data.map_data.map[y][x] == 'N')
		data->file_data.player.angle = 0.5 * M_PI;
	else if (data->file_data.map_data.map[y][x] == 'W')
		data->file_data.player.angle = 1.0 * M_PI;
	else if (data->file_data.map_data.map[y][x] == 'S')
		data->file_data.player.angle = 1.5 * M_PI;
	else if (data->file_data.map_data.map[y][x] == 'E')
		data->file_data.player.angle = 2.0 * M_PI;
	data->file_data.player.x = (x * PIXELS) + centered;
	data->file_data.player.y = (y * PIXELS) + centered;
	data->file_data.player.px = x;
	data->file_data.player.py = y;
	data->file_data.player.dx = cos(data->file_data.player.angle) * MOV_SPEED;
	data->file_data.player.dy = -sin(data->file_data.player.angle) * MOV_SPEED;
	data->graphics.init_dir = true;
}

static bool	draw_gridlines(char	**map, t_general_data *data, int map_height)
{
	int	y;
	int	x;
	int	curr_line_len;
	int	ret_v;
	int	ret_h;

	y = 0;
	while (y < map_height)
	{
		curr_line_len = ft_strlen(map[y]);
		x = 0;
		while (x < curr_line_len)
		{
			ret_v = draw_line(data, x * PIXELS, y * PIXELS, VERTICAL);
			ret_h = draw_line(data, x * PIXELS, y * PIXELS, HORIZONTAL);
			if (!ret_v || !ret_h)
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

static bool	select_draw(char value, t_general_data *data, int x, int y)
{
	bool	ret;

	ret = false;
	if (value == '1')
		ret = draw_square(data, x * PIXELS, y * PIXELS, BLACK, false);
	else if (value == '0')
		ret = draw_square(data, x * PIXELS, y * PIXELS, WHITE, false);
	else if (value == 'X')
		ret = draw_square(data, x * PIXELS, y * PIXELS, GREY, false);
	else if (is_player((const char)value))
	{
		ret = draw_square(data, x * PIXELS, y * PIXELS, WHITE, false);
		if (data->graphics.init_dir == false)
			init_direction(data, x, y);
	}
	return (ret);
}

static bool	draw_cells(char	**map, t_general_data *data, int map_height)
{
	int	y;
	int	x;
	int	curr_line_len;
	int	ret;

	y = 0;
	curr_line_len = 0;
	while (y < map_height)
	{
		curr_line_len = ft_strlen(map[y]);
		x = 0;
		while (x < curr_line_len)
		{
			ret = select_draw(map[y][x], data, x, y);
			if (ret == false)
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	draw_2d_map(t_general_data *data)
{
	if (!draw_cells(data->file_data.map_data.copy, data, \
		data->file_data.map_data.row))
		return (error_msg("Drawing cells"));
	if (!draw_gridlines(data->file_data.map_data.copy, data, \
		data->file_data.map_data.row))
		return (error_msg("Drawing gridlines"));
	if (!draw_player(data, data->graphics.img))
		return (error_msg("Drawing player"));
	return (true);
}
