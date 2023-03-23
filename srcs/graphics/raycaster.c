#include <graphics.h>

static void	draw_ray(mlx_image_t *img, int dx, int dy)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	fprintf(stderr, "j: %d | i: %d\n", j, i); // ? testing
	fprintf(stderr, "dx: %d | dy: %d\n", dx, dy); // ? testing
	while (i <= dy)
	{
		mlx_put_pixel(img, 8, 8 + i, 0xFF0000FF);
		i++;
	}
	while (j <= dx)
	{
		mlx_put_pixel(img, 8 + j, 8, 0xFF0000FF);
		j++;
	}
}

static void	init_ray_orientation(t_general_data *data, t_graphics *graphics)
{
	int	i;

	i = 0;
	data->file_data->player->facing = 'E'; // ? testing
	if (data->file_data->player->facing == 'N')
	{
		/**
		 * we can't draw into negative xy values so not sure...
		*/
		while (i < 32)
		{
			mlx_put_pixel(graphics->images[PLAYER], 8, 8, 0xFF0000FF);
			i++;
		}
	}
	else if (data->file_data->player->facing == 'S')
		draw_ray(graphics->images[PLAYER], 0, 32);
	else if (data->file_data->player->facing == 'W')
	{
		/**
		 * we can't draw into negative xy values so not sure...
		*/
		while (i < 32)
		{
			mlx_put_pixel(graphics->images[PLAYER], 8, 8, 0xFF0000FF);
			i++;
		}
	}
	else if (data->file_data->player->facing == 'E')
		draw_ray(graphics->images[PLAYER], 32, 0);
}

bool	ray_caster(t_general_data *data)
{
	init_ray_orientation(data, data->graphics);
	return (true);
}