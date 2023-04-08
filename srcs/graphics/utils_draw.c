#include <graphics.h>

bool	draw_line(t_general_data *data, int x, int y, t_axis axis)
{
	int	i;

	i = 0;
	while (i < PIXELS)
	{
		if (axis == HORIZONTAL)
		{
			if (!check_put_pixel(data, x + i, y))
				return (false);
			mlx_put_pixel(data->graphics->img, x + i, y, 0x00000000);
		}
		if (axis == VERTICAL)
		{
			if (!check_put_pixel(data, x + i, y))
				return (false);
			mlx_put_pixel(data->graphics->img, x, y + i, 0x00000000);
		}
		i++;
	}
	return (true);
}

bool	draw_square(t_general_data *data, int x, int y, uint32_t color, bool player)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = PIXELS;
	if (player)
		size = 16;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (!check_put_pixel(data, x + i, y + j))
				return (false);
			mlx_put_pixel(data->graphics->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
	return (true);
}
