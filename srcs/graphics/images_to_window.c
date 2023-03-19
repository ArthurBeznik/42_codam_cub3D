#include "cub3D.h"

void	check_player_position(t_general_data *data, \
		t_graphics *graphics, size_t x, size_t y)
{
	if (data->file_data->map_data->map[y][x] == 'N' || \
		data->file_data->map_data->map[y][x] == 'S' || \
		data->file_data->map_data->map[y][x] == 'E' || \
		data->file_data->map_data->map[y][x] == 'W')
	{
		if (mlx_image_to_window(graphics->mlx, \
			graphics->images[PLAYER], x * PIXELS, y * PIXELS) == ERROR)
		{
			error_msg("image_to_window failed");
			terminate(graphics);
		}
	}
}

bool	images_to_window(t_general_data *data, t_graphics *graphics)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (data->file_data->map_data->map[y])
	{
		x = 0;
		while (x < (size_t)data->file_data->map_data->max_line_len)
		{
			if (data->file_data->map_data->map[y][x] == '1')
			{
				if (mlx_image_to_window(graphics->mlx, graphics->images[WALL], \
												x * PIXELS, y * PIXELS) == -1)
				{
					fprintf(stderr, "image_to_window failed\n");
					return (false);
				}
			}
			check_player_position(data, graphics, x, y);
			x++;
		}
		y++;
	}
	return (true);
}
