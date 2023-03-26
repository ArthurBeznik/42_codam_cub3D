#include <graphics.h>

void	movement(t_general_data *data, mlx_t *mlx)
{
	ft_memset(data->graphics->img->pixels, 0, data->graphics->img->width * data->graphics->img->height * sizeof(int));
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || mlx_is_key_down(mlx, MLX_KEY_A))
	{
		data->file_data->player->angle -= ROTATION_SPEED * PI; // ? * 0.01 affects the rotation speed of the direction
		if (data->file_data->player->angle < 0)
			data->file_data->player->angle += RESET_ANGLE; // ? reset PI back if we
		data->file_data->player->dx = cos(data->file_data->player->angle) * MOVE_SPEED;
		data->file_data->player->dy = sin(data->file_data->player->angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) || mlx_is_key_down(mlx, MLX_KEY_D))
	{
		data->file_data->player->angle += ROTATION_SPEED *  PI;
		if (data->file_data->player->angle > 2 * PI)
			data->file_data->player->angle -= RESET_ANGLE;
		data->file_data->player->dx = cos(data->file_data->player->angle) * MOVE_SPEED;
		data->file_data->player->dy = sin(data->file_data->player->angle) * MOVE_SPEED;

	}
	if ((mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W)) \
		&& data->file_data->map_data->copy
			[(int)data->file_data->player->y / PIXELS + (int)data->file_data->player->dy]
			[(int)data->file_data->player->x / PIXELS + (int)data->file_data->player->dx] != '1')
	{
		data->file_data->player->x += data->file_data->player->dx;
		data->file_data->player->y += data->file_data->player->dy;
	}
	if ((mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S)) \
		&& data->file_data->map_data->copy
			[(int)data->file_data->player->y / PIXELS - (int)data->file_data->player->dy]
			[(int)data->file_data->player->x / PIXELS - (int)data->file_data->player->dx] != '1')
	{
		data->file_data->player->x -= data->file_data->player->dx;
		data->file_data->player->y -= data->file_data->player->dy;
	}
	draw_2d_map(data, data->graphics->img);
}

void	captain(void *param)
{
	t_general_data		*data2;

	data2 = (t_general_data *)param;
	// log_positions(data2, "captain", 'P'); // ? testing
	if (mlx_is_key_down(data2->graphics->mlx, MLX_KEY_ESCAPE))
		terminate(data2->graphics);
	movement(data2, data2->graphics->mlx);
	// log_positions(data2, "captain", 'P'); // ? testing
}
