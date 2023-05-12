#include <cub3D.h>

void	move_forward(t_general_data *data)
{
	if (data->file_data.map_data.copy[(int)(data->graphics.dda.pos_y)] \
		[(int)(data->graphics.dda.pos_x + \
			data->graphics.dda.dir_x * MOV_SPEED)] != '1')
	{
		data->graphics.dda.pos_x += data->graphics.dda.dir_x * MOV_SPEED;
		data->file_data.player.x = data->graphics.dda.pos_x * PIXELS;
	}
	if (data->file_data.map_data.copy[(int)(data->graphics.dda.pos_y + \
		data->graphics.dda.dir_y * \
			MOV_SPEED)][(int)(data->graphics.dda.pos_x)] != '1')
	{
		data->graphics.dda.pos_y += data->graphics.dda.dir_y * MOV_SPEED;
		data->file_data.player.y = data->graphics.dda.pos_y * PIXELS;
	}
}

void	move_backward(t_general_data *data)
{
	if (data->file_data.map_data.copy[(int)(data->graphics.dda.pos_y)] \
		[(int)(data->graphics.dda.pos_x - \
			data->graphics.dda.dir_x * MOV_SPEED)] != '1')
	{
		data->graphics.dda.pos_x -= data->graphics.dda.dir_x * MOV_SPEED;
		data->file_data.player.x = data->graphics.dda.pos_x * PIXELS;
	}
	if (data->file_data.map_data.copy[(int)(data->graphics.dda.pos_y - \
		data->graphics.dda.dir_y * \
			MOV_SPEED)][(int)(data->graphics.dda.pos_x)] != '1')
	{
		data->graphics.dda.pos_y -= data->graphics.dda.dir_y * MOV_SPEED;
		data->file_data.player.y = data->graphics.dda.pos_y * PIXELS;
	}
}

void	rotate_left(t_general_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->graphics.dda.dir_x;
	data->graphics.dda.dir_x = data->graphics.dda.dir_x * cos(-ROT_SPEED) - \
		data->graphics.dda.dir_y * sin(-ROT_SPEED);
	data->graphics.dda.dir_y = old_dir_x * sin(-ROT_SPEED) + \
		data->graphics.dda.dir_y * cos(-ROT_SPEED);
	old_plane_x = data->graphics.dda.plane_x;
	data->graphics.dda.plane_x = data->graphics.dda.plane_x * \
		cos(-ROT_SPEED) - data->graphics.dda.plane_y * sin(-ROT_SPEED);
	data->graphics.dda.plane_y = old_plane_x * sin(-ROT_SPEED) + \
		data->graphics.dda.plane_y * cos(-ROT_SPEED);
}

void	rotate_right(t_general_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->graphics.dda.dir_x;
	data->graphics.dda.dir_x = data->graphics.dda.dir_x * cos(ROT_SPEED) - \
		data->graphics.dda.dir_y * sin(ROT_SPEED);
	data->graphics.dda.dir_y = old_dir_x * sin(ROT_SPEED) + \
		data->graphics.dda.dir_y * cos(ROT_SPEED);
	old_plane_x = data->graphics.dda.plane_x;
	data->graphics.dda.plane_x = data->graphics.dda.plane_x * \
		cos(ROT_SPEED) - data->graphics.dda.plane_y * sin(ROT_SPEED);
	data->graphics.dda.plane_y = old_plane_x * sin(ROT_SPEED) + \
		data->graphics.dda.plane_y * cos(ROT_SPEED);
}
