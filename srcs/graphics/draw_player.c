#include <cub3D.h>

static void	calc_draw(t_general_data *data)
{
	data->graphics.draw.x1 = data->file_data.player.x;
	data->graphics.draw.y1 = data->file_data.player.y;
	data->graphics.draw.x2 = data->file_data.player.x + \
		(data->graphics.dda.dir_x * 16);
	data->graphics.draw.y2 = data->file_data.player.y + \
		(data->graphics.dda.dir_y * 16);
	data->graphics.draw.dx = (data->graphics.draw.x2 - data->graphics.draw.x1);
	data->graphics.draw.dy = (data->graphics.draw.y2 - data->graphics.draw.y1);
	if (fabs(data->graphics.draw.dx) >= fabs(data->graphics.draw.dy))
		data->graphics.draw.step = fabs(data->graphics.draw.dx);
	else
		data->graphics.draw.step = fabs(data->graphics.draw.dy);
	data->graphics.draw.dx = data->graphics.draw.dx / data->graphics.draw.step;
	data->graphics.draw.dy = data->graphics.draw.dy / data->graphics.draw.step;
	data->graphics.draw.x = data->graphics.draw.x1;
	data->graphics.draw.y = data->graphics.draw.y1;
}

static void	init_draw_data(t_general_data *data)
{
	data->graphics.draw.x = NA;
	data->graphics.draw.y = NA;
	data->graphics.draw.dx = NA;
	data->graphics.draw.dy = NA;
	data->graphics.draw.x1 = NA;
	data->graphics.draw.y1 = NA;
	data->graphics.draw.x2 = NA;
	data->graphics.draw.y2 = NA;
	data->graphics.draw.step = NA;
}

static bool	draw_direction(t_general_data *data, mlx_image_t *img)
{
	int		i;

	init_draw_data(data);
	calc_draw(data);
	i = 1;
	while (i <= data->graphics.draw.step)
	{
		mlx_put_pixel(img, data->graphics.draw.x, data->graphics.draw.y, RED);
		data->graphics.draw.x += data->graphics.draw.dx;
		data->graphics.draw.y += data->graphics.draw.dy;
		i++;
	}
	return (true);
}

bool	draw_player(t_general_data *data, mlx_image_t *img)
{
	int	x;
	int	y;
	int	p_size;
	int	centered;

	p_size = 16;
	centered = p_size / 2;
	x = (int)data->file_data.player.x;
	while (x - p_size < data->file_data.player.x)
	{
		y = (int)data->file_data.player.y;
		while (y - p_size < data->file_data.player.y)
		{
			if (!check_put_pixel(data, x - centered, y - centered))
				return (false);
			mlx_put_pixel(img, x - centered, y - centered, YELLOW);
			y++;
		}
		x++;
	}
	if (!draw_direction(data, data->graphics.img))
		return (false);
	return (true);
}
