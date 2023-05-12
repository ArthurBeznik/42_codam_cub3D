#include <cub3D.h>

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
			mlx_put_pixel(data->graphics.img, x + i, y, GREY);
		}
		if (axis == VERTICAL)
		{
			if (!check_put_pixel(data, x + i, y))
				return (false);
			mlx_put_pixel(data->graphics.img, x, y + i, GREY);
		}
		i++;
	}
	return (true);
}

bool	draw_square(t_general_data *data, int x, int y, uint32_t color)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = PIXELS;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (!check_put_pixel(data, x + i, y + j))
				return (false);
			mlx_put_pixel(data->graphics.img, x + i, y + j, color);
			j++;
		}
		i++;
	}
	return (true);
}

int	get_rgba(mlx_texture_t *texture, int x, int y)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = texture->pixels[y * texture->width * 4 + (x * 4)];
	g = texture->pixels[y * texture->width * 4 + (x * 4) + 1];
	b = texture->pixels[y * texture->width * 4 + (x * 4) + 2];
	a = texture->pixels[y * texture->width * 4 + (x * 4) + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}
