#include <graphics.h>

void	init_wall_collision(t_general_data *data, t_wall_collision *wall)
{
	if (data->file_data->player->dx < 0)
		wall->xo = -20;
	else
		wall->xo = 20;
	if (data->file_data->player->dy < 0)
		wall->yo = -20;
	else
		wall->yo = 20;
	wall->ipx = (int)data->file_data->player->x / PIXELS;
	wall->ipx_add_xo = (int)(data->file_data->player->x + wall->xo) / PIXELS;
	wall->ipx_sub_xo = (int)(data->file_data->player->x - wall->xo) / PIXELS;
	wall->ipy = (int)data->file_data->player->y / PIXELS;
	wall->ipy_add_yo = (int)(data->file_data->player->y + wall->yo) / PIXELS;
	wall->ipy_sub_yo = (int)(data->file_data->player->y - wall->yo) / PIXELS;
}

void	check_w_s_keys(t_general_data *data, mlx_t *mlx, t_wall_collision wall)
{
	if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W))
	{
		if (data->file_data->map_data->copy[wall.ipy][wall.ipx_add_xo] != '1')
			data->file_data->player->x += data->file_data->player->dx;
		if (data->file_data->map_data->copy[wall.ipy_add_yo][wall.ipx] != '1')
			data->file_data->player->y += data->file_data->player->dy;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S))
	{
		if (data->file_data->map_data->copy[wall.ipy][wall.ipx_sub_xo] != '1')
			data->file_data->player->x -= data->file_data->player->dx;
		if (data->file_data->map_data->copy[wall.ipy_sub_yo][wall.ipx] != '1')
			data->file_data->player->y -= data->file_data->player->dy;
	}
}

void	movement(t_general_data *data, mlx_t *mlx)
{
	t_wall_collision	wall;

	init_wall_collision(data, &wall);
	ft_memset(data->graphics->img->pixels, 0, data->graphics->img->width * \
				data->graphics->img->height * sizeof(int));
	ft_memset(data->graphics->img_3d->pixels, 0, 500 * 500 * sizeof(int));
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || mlx_is_key_down(mlx, MLX_KEY_A))
	{
		data->file_data->player->angle += ROTATION_SPEED * M_PI;
		if (data->file_data->player->angle < 0)
			data->file_data->player->angle += RESET_ANGLE;
		data->file_data->player->dx = cos(data->file_data->player->angle) * S;
		data->file_data->player->dy = -sin(data->file_data->player->angle) * S;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) || mlx_is_key_down(mlx, MLX_KEY_D))
	{
		data->file_data->player->angle -= ROTATION_SPEED * M_PI;
		if (data->file_data->player->angle > 2 * M_PI)
			data->file_data->player->angle -= RESET_ANGLE;
		data->file_data->player->dx = cos(data->file_data->player->angle) * S;
		data->file_data->player->dy = -sin(data->file_data->player->angle) * S;
	}
	check_w_s_keys(data, mlx, wall);
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
	if (!ray_caster(data2))
		terminate(data2->graphics);
	// log_positions(data2, "captain", 'P'); // ? testing
}
