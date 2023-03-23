#include <graphics.h>

void draw_direction(t_general_data *data, mlx_image_t *img, double angle)
{
	int		i;
	int		size;
	double	x1;
    double	y1;

	size = 32;
	i = 0;
	while (i < size)
	{
		x1 = (i * cos((angle))) + data->file_data->player->x + 1;
        y1 = (i * sin((angle))) + data->file_data->player->y + 1;
		fprintf(stderr, "x1 | y1: %f | %f\n", x1, y1);
		fprintf(stderr, "px | py: %f | %f\n", data->file_data->player->x, data->file_data->player->y);
		fprintf(stderr, "h | w: %lld | %lld\n", data->graphics->height, data->graphics->width);
		if (x1 < data->graphics->width && x1 > 0 && y1 < data->graphics->height && y1 > 0)
			mlx_put_pixel(img, x1, y1, 0xFF000090);
		i++;
	}
}

/**
 * ! verifiy this is actually correct because once setting the size to 64
 * ! the player goes over gridlines
*/
void	draw_player(t_general_data *data, mlx_image_t *img)
{
	int	x;
	int	y;
	int	size;

	size = 32;
	x = (int)data->file_data->player->x;
	while (data->file_data->player->x > x - size)
	{
		y = (int)data->file_data->player->y;
		while (y - size < data->file_data->player->y)
		{
            mlx_put_pixel(img, x - size / 2, y - size / 2, 0xFFFF00FF);
			y++;
		}
		x++;
	}
	draw_direction(data, data->graphics->img, data->file_data->player->angle);
}