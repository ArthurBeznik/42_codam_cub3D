#include <graphics.h>

void	fix_angle(t_general_data *data)
{
	if (data->file_data->player->angle < 0)
		data->file_data->player->angle += RESET_ANGLE;
	if (data->file_data->player->angle > 2 * M_PI)
		data->file_data->player->angle -= RESET_ANGLE;
}

void	movement(t_general_data *data, mlx_t *mlx)
{
	ft_memset(data->graphics->img->pixels, 0, data->graphics->img->width * data->graphics->img->height * sizeof(int));
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || mlx_is_key_down(mlx, MLX_KEY_A))
	{
		data->file_data->player->angle += ROTATION_SPEED * M_PI;
		// data->file_data->player->angle += M_PI;
		fix_angle(data);
		// if (data->file_data->player->angle < 0)
		// 	data->file_data->player->angle += RESET_ANGLE;
		data->file_data->player->dx = cos(data->file_data->player->angle) * MOVE_SPEED;
		data->file_data->player->dy = -sin(data->file_data->player->angle) * MOVE_SPEED;
		// data->file_data->player->dx = cos(data->file_data->player->angle);
		// data->file_data->player->dy = -sin(data->file_data->player->angle);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) || mlx_is_key_down(mlx, MLX_KEY_D))
	{
		data->file_data->player->angle -= ROTATION_SPEED * M_PI;
		// data->file_data->player->angle -= M_PI;
		// if (data->file_data->player->angle > 2 * M_PI)
		// 	data->file_data->player->angle -= RESET_ANGLE;
		fix_angle(data);
		data->file_data->player->dx = cos(data->file_data->player->angle) * MOVE_SPEED;
		data->file_data->player->dy = -sin(data->file_data->player->angle) * MOVE_SPEED;
		// data->file_data->player->dx = cos(data->file_data->player->angle);
		// data->file_data->player->dy = -sin(data->file_data->player->angle);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W))
	{
		data->file_data->player->x += data->file_data->player->dx;
		data->file_data->player->y += data->file_data->player->dy;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S))
	{
		data->file_data->player->x -= data->file_data->player->dx;
		data->file_data->player->y -= data->file_data->player->dy;
	}
}

void	captain(void *param)
{
	t_general_data		*data2;

	data2 = (t_general_data *)param;
	// log_positions(data2, "captain", 'P'); // ? testing
	if (mlx_is_key_down(data2->graphics->mlx, MLX_KEY_ESCAPE))
		terminate(data2->graphics);
	movement(data2, data2->graphics->mlx);
	draw_2d_map(data2);
	// ray_casting(data2);
	if (!test_ray(data2))
		terminate(data2->graphics);
	// log_positions(data2, "captain", 'P'); // ? testing
}
