#include <graphics.h>

/**
 * See degree to radian conversion 
 * 	. degree to radian => nb of degrees * M_PI / 180
 * 	. radian to degree => nb of radians * 180 / M_PI
 * To mesure radians, we start from the right side of the circle and move counter-clockwise.
 * A few important mesures:
 * 	. 0 or 360 degrees = 2 M_PI
 * 	. 90 degrees = M_PI / 2 (or (3 * M_PI / 2) if we already did a full circle)
 * 	. 180 degrees = M_PI (or (6 * M_PI / 6) if we already did a full circle)
 * 	. 270 degrees = 3 M_PI / 2
 * So if we translate that to our program, it gives us:
 * 	. N = 90 degrees = 1.5 * M_PI
*/
static void	init_direction(t_general_data *data, int x, int y)
{
	int	centered;

	centered = PIXELS / 2;
	if (data->file_data->map_data->map[y][x] == 'N')
	{
		data->file_data->player->angle = 0.5 * M_PI;
		// data->graphics->dda->dir_x = 0;
		// data->graphics->dda->dir_y = -1;
	}
	else if (data->file_data->map_data->map[y][x] == 'W')
		data->file_data->player->angle = 1.0 * M_PI;
	else if (data->file_data->map_data->map[y][x] == 'S')
		data->file_data->player->angle = 1.5 * M_PI;
	else if (data->file_data->map_data->map[y][x] == 'E')
		data->file_data->player->angle = 2.0 * M_PI;
	// fprintf(stderr, "x: %d | y: %d\n", x, y); // ? testing
	// log_val(data, "init_dir", 'A'); // ? testing
	data->file_data->player->x = (x * PIXELS) + centered; // (+ PIXELS / 2) => gets the exact player x
	data->file_data->player->y = (y * PIXELS) + centered; // "" gets the exact player y
	data->file_data->player->px = x;
	data->file_data->player->py = y;
	// log_val(data, "init_dir", 'P'); // ? testing
	// log_val(data, "init_dir", 'G'); // ? testing
	data->file_data->player->dx = cos(data->file_data->player->angle) * MOV_SPEED; // ? * 5 because these are very small values
	data->file_data->player->dy = -sin(data->file_data->player->angle) * MOV_SPEED; // ? also affects the speed of the player
	// log_val(data, "init_dir", 'D'); // ? testing
	data->graphics->init_dir = true;
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
			if (map[y][x] == '1')
				ret = draw_square(data, x * PIXELS, y * PIXELS, BLACK, false);
			else if (map[y][x] == '0')
				ret = draw_square(data, x * PIXELS, y * PIXELS, WHITE, false);
			else if (map[y][x] == 'X')
				ret = draw_square(data, x * PIXELS, y * PIXELS, GREY, false);
			else if (is_player((const char)map[y][x]))
			{
				ret = draw_square(data, x * PIXELS, y * PIXELS, WHITE, false);
				if (data->graphics->init_dir == false)
					init_direction(data, x, y);
			}
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
	if (!draw_cells(data->file_data->map_data->copy, data, data->file_data->map_data->row))
		return (error_msg("Drawing cells"));
	if (!draw_gridlines(data->file_data->map_data->copy, data, data->file_data->map_data->row))
		return (error_msg("Drawing gridlines"));
	if (!draw_player(data, data->graphics->img))
		return (error_msg("Drawing player"));
	return (true);
}
