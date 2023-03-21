#include <graphics.h>

void	draw_line(mlx_image_t* img, int x, int y, int orientation)
{
    int	i;

	i = 0;
	while (i < PIXELS)
	{
		if (orientation == H)
			mlx_put_pixel(img, x + i, y, 0x00000000);
		if (orientation == V)
			mlx_put_pixel(img, x, y + i, 0x00000000);
		i++;
	}
}

void	draw_square(mlx_image_t* img, int x, int y, uint32_t color, bool player)
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
            mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
