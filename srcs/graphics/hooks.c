#include <cub3D.h>

void	movement(t_general_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	ft_memset(data->graphics.img->pixels, 0, data->graphics.img->width * \
				data->graphics.img->height * sizeof(int));
	ft_memset(data->graphics.img_3d->pixels, 0, data->graphics.img->width * \
				data->graphics.img->height * sizeof(int));

	// fprintf(stderr, "pos_x | pos_y | value : %f | %f | %c\n", data->graphics.dda.pos_x, data->graphics.dda.pos_y, data->file_data.map_data.copy[(int)data->graphics.dda.pos_y][(int)data->graphics.dda.pos_x]); // ? testing
	// fprintf(stderr, "player_x | player_y : %f | %f\n", data->file_data.player.x, data->file_data.player.y); // ? testing
	// fprintf(stderr, "dir_x | dir_y : %f | %f\n", data->graphics.dda.dir_x, data->graphics.dda.dir_y); // ? testing
	// fprintf(stderr, "plane_x | plane_y : %f | %f\n", data->graphics.dda.plane_x, data->graphics.dda.plane_y); // ? testing

	/* move forward if no wall in front of you */
	if (mlx_is_key_down(data->graphics.mlx, MLX_KEY_UP) || mlx_is_key_down(data->graphics.mlx, MLX_KEY_W))
	{
		if (data->file_data.map_data.copy[(int)(data->graphics.dda.pos_y)][(int)(data->graphics.dda.pos_x + data->graphics.dda.dir_x * MOV_SPEED)] != '1')
		{
			data->graphics.dda.pos_x += data->graphics.dda.dir_x * MOV_SPEED;
			data->file_data.player.x = data->graphics.dda.pos_x * PIXELS;
		}
		if (data->file_data.map_data.copy[(int)(data->graphics.dda.pos_y + data->graphics.dda.dir_y * MOV_SPEED)][(int)(data->graphics.dda.pos_x)] != '1')
		{
			data->graphics.dda.pos_y += data->graphics.dda.dir_y * MOV_SPEED;
			data->file_data.player.y = data->graphics.dda.pos_y * PIXELS;
		}
	}
	/* move backwards if no wall behind you */
	if (mlx_is_key_down(data->graphics.mlx, MLX_KEY_DOWN) || mlx_is_key_down(data->graphics.mlx, MLX_KEY_S))
	{
		if (data->file_data.map_data.copy[(int)(data->graphics.dda.pos_y)][(int)(data->graphics.dda.pos_x - data->graphics.dda.dir_x * MOV_SPEED)] != '1')
		{
			data->graphics.dda.pos_x -= data->graphics.dda.dir_x * MOV_SPEED;
			data->file_data.player.x = data->graphics.dda.pos_x * PIXELS;
		}
		if (data->file_data.map_data.copy[(int)(data->graphics.dda.pos_y - data->graphics.dda.dir_y * MOV_SPEED)][(int)(data->graphics.dda.pos_x)] != '1')
		{
			data->graphics.dda.pos_y -= data->graphics.dda.dir_y * MOV_SPEED;
			data->file_data.player.y = data->graphics.dda.pos_y * PIXELS;
		}
	}
	/* rotate to the right */
	if (mlx_is_key_down(data->graphics.mlx, MLX_KEY_RIGHT) || mlx_is_key_down(data->graphics.mlx, MLX_KEY_D))
	{
		/* both camera direction and camera plane must be rotated */
		old_dir_x = data->graphics.dda.dir_x;
		data->graphics.dda.dir_x = data->graphics.dda.dir_x * cos(ROT_SPEED) - data->graphics.dda.dir_y * sin(ROT_SPEED);
		data->graphics.dda.dir_y = old_dir_x * sin(ROT_SPEED) + data->graphics.dda.dir_y * cos(ROT_SPEED);
		old_plane_x = data->graphics.dda.plane_x;
		data->graphics.dda.plane_x = data->graphics.dda.plane_x * cos(ROT_SPEED) - data->graphics.dda.plane_y * sin(ROT_SPEED);
		data->graphics.dda.plane_y = old_plane_x * sin(ROT_SPEED) + data->graphics.dda.plane_y * cos(ROT_SPEED);
	}
	/* rotate to the left */
	if (mlx_is_key_down(data->graphics.mlx, MLX_KEY_LEFT) || mlx_is_key_down(data->graphics.mlx, MLX_KEY_A))
	{
		/* both camera direction and camera plane must be rotated */
		old_dir_x = data->graphics.dda.dir_x;
		data->graphics.dda.dir_x = data->graphics.dda.dir_x * cos(-ROT_SPEED) - data->graphics.dda.dir_y * sin(-ROT_SPEED);
		data->graphics.dda.dir_y = old_dir_x * sin(-ROT_SPEED) + data->graphics.dda.dir_y * cos(-ROT_SPEED);
		old_plane_x = data->graphics.dda.plane_x;
		data->graphics.dda.plane_x = data->graphics.dda.plane_x * cos(-ROT_SPEED) - data->graphics.dda.plane_y * sin(-ROT_SPEED);
		data->graphics.dda.plane_y = old_plane_x * sin(-ROT_SPEED) + data->graphics.dda.plane_y * cos(-ROT_SPEED);
	}
	// fprintf(stderr, "dir_x | dir_y : %f | %f\n", data->graphics.dda.dir_x, data->graphics.dda.dir_y); // ? testing
}

void	captain(void *param)
{
	t_general_data		*data2;

	data2 = (t_general_data *)param;
	// log_val(data2, "captain", 'P'); // ? testing
	if (mlx_is_key_down(data2->graphics.mlx, MLX_KEY_ESCAPE))
		terminate(&data2->graphics);
	movement(data2);
	if (!draw_2d_map(data2))
		terminate(&data2->graphics);
	if (!cast_ray(data2))
		terminate(&data2->graphics);
	// log_val(data2, "captain", 'P'); // ? testing
}
