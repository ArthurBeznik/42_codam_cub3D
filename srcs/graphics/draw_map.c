#include <graphics.h>

static void	init_direction(t_general_data *data, mlx_image_t *img, int x, int y)
{
	if (data->file_data->map_data->map[y][x] == 'N')
		data->file_data->player->angle = 1.5 * PI;
	else if (data->file_data->map_data->map[y][x] == 'S')
		data->file_data->player->angle = 0.5 * PI;
	else if (data->file_data->map_data->map[y][x] == 'W')
		data->file_data->player->angle = 1.0 * PI;
	else if (data->file_data->map_data->map[y][x] == 'E')
		data->file_data->player->angle = 2.0 * PI;
	// fprintf(stderr, "x: %d | y: %d\n", x, y); // ? testing
	// fprintf(stderr, "angle: %f\n", data->file_data->player->angle); // ? testing
	data->file_data->player->x = (x * PIXELS) + PIXELS / 2;
	data->file_data->player->y = (y * PIXELS) + PIXELS / 2;
	// fprintf(stderr, "x: %f | y: %f\n", data->file_data->player->x, data->file_data->player->y); // ? testing
	data->file_data->player->dx = lround((cos(data->file_data->player->angle)) * 5);
	data->file_data->player->dy = lround((sin(data->file_data->player->angle)) * 5);
	data->graphics->init_dir = true;
}

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

static void	draw_cells(char	**map, t_general_data *data, mlx_image_t *img, int map_height)
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
			else if (map[y][x] == '0')
				draw_square(img, x * PIXELS, y * PIXELS, 0xFFFFFFFF, false);
			else if (map[y][x] == 'X')
				draw_square(img, x * PIXELS, y * PIXELS, 0x00000000, false);
			else if (is_player((const char)map[y][x]))
			{
				draw_square(img, x * PIXELS, y * PIXELS, 0xFFFFFFFF, false);
				if (data->graphics->init_dir == false)
					init_direction(data, img, x, y);
			}
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
void	draw_2d_map(t_general_data *data, mlx_image_t *img)
{
	int		y;
	int		x;
	int		map_height;
	int		curr_line_len;
	char	**copy;

	map_height = data->file_data->map_data->rows_count;
	copy = copy_map(data->file_data->map_data->map, data->file_data->map_data->rows_count);
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
	draw_cells(copy, data, img, map_height);
	draw_gridlines(copy, img, map_height);
	free_2d(copy);
	draw_player(data, data->graphics->img);
}
