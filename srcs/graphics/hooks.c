#include <cub3D.h>

static void	detect_key(t_general_data *data)
{
	if (mlx_is_key_down(data->graphics.mlx, MLX_KEY_UP) || \
		mlx_is_key_down(data->graphics.mlx, MLX_KEY_W))
		move_forward(data);
	if (mlx_is_key_down(data->graphics.mlx, MLX_KEY_DOWN) || \
		mlx_is_key_down(data->graphics.mlx, MLX_KEY_S))
		move_backward(data);
	if (mlx_is_key_down(data->graphics.mlx, MLX_KEY_RIGHT) || \
		mlx_is_key_down(data->graphics.mlx, MLX_KEY_D))
		rotate_right(data);
	if (mlx_is_key_down(data->graphics.mlx, MLX_KEY_LEFT) || \
		mlx_is_key_down(data->graphics.mlx, MLX_KEY_A))
		rotate_left(data);
}

void	captain(void *param)
{
	t_general_data		*data2;

	data2 = (t_general_data *)param;
	if (mlx_is_key_down(data2->graphics.mlx, MLX_KEY_ESCAPE))
		terminate(&data2->graphics, EXIT_SUCCESS);
	detect_key(data2);
	if (!cast_ray(data2))
		terminate(&data2->graphics, EXIT_FAILURE);
}

/**
 * ? Display 2D map
*/
// void	captain(void *param)
// {
// 	t_general_data		*data2;

// 	data2 = (t_general_data *)param;
// 	if (mlx_is_key_down(data2->graphics.mlx, MLX_KEY_ESCAPE))
// 		terminate(&data2->graphics);
// 	detect_key(data2);
// 	if (!draw_2d_map(data2))
// 		terminate(&data2->graphics);
// 	if (!cast_ray(data2))
// 		terminate(&data2->graphics);
// }
