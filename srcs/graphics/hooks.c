#include <graphics.h>

void	movement(t_general_data *data, size_t y, size_t x)
{
	if (mlx_is_key_down(data->graphics->mlx, MLX_KEY_S) \
						&& data->file_data->map_data->map[y + 1][x] != '1')
			data->graphics->images[PLAYER]->instances[0].y += PIXELS;
	else if (mlx_is_key_down(data->graphics->mlx, MLX_KEY_A) \
						&& data->file_data->map_data->map[y][x - 1] != '1')
			data->graphics->images[PLAYER]->instances[0].x -= PIXELS;
	else if (mlx_is_key_down(data->graphics->mlx, MLX_KEY_D) \
						&& data->file_data->map_data->map[y][x + 1] != '1')
		data->graphics->images[PLAYER]->instances[0].x += PIXELS;
	else if (mlx_is_key_down(data->graphics->mlx, MLX_KEY_W) \
						&& data->file_data->map_data->map[y - 1][x] != '1')
		data->graphics->images[PLAYER]->instances[0].y -= PIXELS;
}

void	hook(void *param)
{
	size_t				x;
	size_t				y;
	t_general_data		*data2;

	data2 = (t_general_data *)param;
	x = (data2->graphics->images[PLAYER]->instances[0].x / PIXELS);
	y = (data2->graphics->images[PLAYER]->instances[0].y / PIXELS);
	if (mlx_is_key_down(data2->graphics->mlx, MLX_KEY_ESCAPE))
		terminate(data2->graphics);
	movement(data2, y, x);
}
