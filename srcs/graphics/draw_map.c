#include <graphics.h>

static void	draw_gridlines(char	**map, mlx_image_t *img, int map_height)
{
	int	y;
	int	x;
	int	curr_line_len;

	y = 0;
	while (y < map_height)
	{
		curr_line_len = ft_strlen(map[y]);
		x = 0;
		while (x < curr_line_len)
		{
			draw_line(img, x * PIXELS, y * PIXELS, V);
			draw_line(img, x * PIXELS, y * PIXELS, H);
			x++;
		}
		y++;
	}
}

static void	draw_cells(char	**map, mlx_image_t *img, int map_height)
{
	int	y;
	int	x;
	int	curr_line_len;

	y = 0;
	curr_line_len = 0;
	while (y < map_height)
	{
		curr_line_len = ft_strlen(map[y]);
		x = 0;
		while (x < curr_line_len)
		{
			if (map[y][x] == '1')
				draw_square(img, x * PIXELS, y * PIXELS, 0x000000FF, false);
			else if (map[y][x] == '0' || is_player((const char)map[y][x]))
				draw_square(img, x * PIXELS, y * PIXELS, 0xFFFFFFFF, false);
			else if (map[y][x] == 'X')
				draw_square(img, x * PIXELS, y * PIXELS, 0x00000000, false);
			x++;
		}
		y++;
	}
}

/**
 * Draws the map in 2D with gridlines.
 * 	1. Copies the map and replaces the spaces with 'X'.
 * 	2. Draws cells.
 * 	3. Draws gridlines.
*/
static void	draw_2d_map(t_general_data *data, mlx_image_t *img)
{
	int		y;
	int		x;
	int		map_height;
	int		curr_line_len;
	char	**copy;

	map_height = data->file_data->map_data->rows_count;
	copy = copy_map(data->file_data->map_data->map, \
		data->file_data->map_data->rows_count);
	y = 0;
	while (y < map_height)
	{
		curr_line_len = ft_strlen(copy[y]);
		x = 0;
		while (x < curr_line_len)
		{
			if (copy[y][x] == ' ')
				copy[y][x] = 'X';
			x++;
		}
		y++;
	}
	draw_cells(copy, img, map_height);
	draw_gridlines(copy, img, map_height);
	free_2d(copy);
}

/**
 * 24 because player is size 16, so 64 - 16 = 48
 * 48 / 2 = 24
 * supposedly the center of a cell but it might be buggy
*/
static bool	draw_player(t_general_data *data, mlx_image_t *img)
{
	draw_square(img, 0, 0, 0xFFFF00FF, true);
	if ((mlx_image_to_window(data->graphics->mlx, data->graphics->images[PLAYER], \
		(data->file_data->player->x * PIXELS) + 24, \
		(data->file_data->player->y * PIXELS) + 24)) < 0)
		return (false);
	return (true);
}

bool	map_viewer(t_general_data *data)
{
	draw_2d_map(data, data->graphics->images[IMG_FLOOR]);
	if ((mlx_image_to_window(data->graphics->mlx, \
			data->graphics->images[IMG_FLOOR], 0, 0) < 0))
		return (error_msg("floor to window"));
	if (!draw_player(data, data->graphics->images[PLAYER]))
		return (error_msg("player to window"));
	// if (!draw_ray(data, data->graphics->images[PLAYER]))
	// 	return (error_msg("rays to window"));
	return (true);
}
