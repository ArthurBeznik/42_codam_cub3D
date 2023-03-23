#include <graphics.h>

/**
 * TODO fix this shit
*/
void	movement(t_general_data *data, mlx_t *mlx, size_t y, size_t x)
{
	// double	angle;

	// angle = data->file_data->player->angle;
	ft_memset(data->graphics->img->pixels, 0, data->graphics->img->width * data->graphics->img->height * sizeof(int));
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		data->file_data->player->angle -= 0.05 * PI;
		if (data->file_data->player->angle < 0)
			data->file_data->player->angle += 2 * PI;
		data->file_data->player->dx = cos(data->file_data->player->angle) * 5;
		data->file_data->player->dy = sin(data->file_data->player->angle) * 5;
		
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		data->file_data->player->angle += 0.05 *  PI;
		if (data->file_data->player->angle > 2 * PI)
			data->file_data->player->angle -= 2 * PI;
		data->file_data->player->dx = cos(data->file_data->player->angle) * 5;
		data->file_data->player->dy = sin(data->file_data->player->angle) * 5;
		
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		data->file_data->player->y += data->file_data->player->dx;
		data->file_data->player->x += data->file_data->player->dy;
		
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		data->file_data->player->y -= data->file_data->player->dx;
		data->file_data->player->x -= data->file_data->player->dy;
		
	}
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		data->file_data->player->y += data->file_data->player->dx;
		data->file_data->player->x += data->file_data->player->dy;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		data->file_data->player->y -= data->file_data->player->dx;
		data->file_data->player->x -= data->file_data->player->dy;
	}
	draw_2d_map(data, data->graphics->img);
}

void	captain(void *param)
{
	size_t				x;
	size_t				y;
	t_general_data		*data2;

	data2 = (t_general_data *)param;
	// log_positions(data2, 'I', "IN"); // ? testing
	// log_positions(data2, 'P', "IN"); // ? testing
	// fprintf(stderr, "x: %zu | y: %zu\n", x, y);
	if (mlx_is_key_down(data2->graphics->mlx, MLX_KEY_ESCAPE))
		terminate(data2->graphics);
	movement(data2, data2->graphics->mlx, y, x);
	// log_positions(data2, 'P', "OUT"); // ? testing
	// log_positions(data2, 'I', "OUT"); // ? testing
}
