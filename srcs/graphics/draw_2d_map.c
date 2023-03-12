#include <graphics.h>

static void ft_hook(void* param)
{
	t_general_data		*data2;

	data2 = (t_general_data *)param;
	// printf("WIDTH: %d | HEIGHT: %d\n", WIDTH, HEIGHT);
}

static void draw_h_line(mlx_image_t* img, int x, int y, int size, int color)
{
    int	i;

    for (i = 0; i < size; i++)
	{
			// fprintf(stderr, "x: %d | y: %d\n", j, i);
            mlx_put_pixel(img, x + i, y, color);
    }
}

static void draw_v_line(mlx_image_t* img, int x, int y, int size, int color)
{
    int	i;

    for (i = 0; i < size; i++)
	{
			// fprintf(stderr, "x: %d | y: %d\n", j, i);
            mlx_put_pixel(img, x, y + i, color);
    }
}

static void draw_square(mlx_image_t* img, int x, int y, int size, int color)
{
    int	i;
	int	j;

    for (i = 0; i < size; i++)
	{
        for (j = 0; j < size; j++)
		{
			// fprintf(stderr, "x: %d | y: %d\n", j, i);
            mlx_put_pixel(img, x + i, y + j, color);
        }
    }
}

static void	draw_circle(mlx_image_t* img, int x, int y, int radius, int color)
{
	int		i;
	int		j;

	i = -radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			if (i*i + j*j <= radius * radius)
				mlx_put_pixel(img, x+i, y+j, color);
			j++;
		}
		i++;
	}
}

// Function to draw the map and grid
static void draw_2d_map(t_general_data *data, mlx_image_t* img)
{
    int	y; 
	int	x;

    for (y = 0; y < 5; y++)
	{
        for (x = 0; x < 6; x++)
		{
			fprintf(stderr, "x: %d | y: %d | %c\n", x, y, data->file_data->map_data->map[y][x]);
            if (data->file_data->map_data->map[y][x] == '1')
			{
                // Draw black square for 1
                draw_square(img, x * PIXELS, y * PIXELS, PIXELS, 255);
            }
			else if (data->file_data->map_data->map[y][x] == 'S')
			{
				// Draw dot for player
				draw_circle(img, x * PIXELS + 32, y * PIXELS + 32, 8, 255);
            }
			else
			{
                // Draw white square for 0
                draw_square(img, x * PIXELS, y * PIXELS, PIXELS, 0);
            }
        }
    }

    // Draw grid lines
	for (y = 0; y < 5; y++)
	{
        for (x = 0; x < 6; x++)
		{
			draw_h_line(img, x * PIXELS, y * PIXELS, PIXELS, 100);
			draw_v_line(img, x * PIXELS, y * PIXELS, PIXELS, 100);
        }
    }

}

bool draw_map(t_general_data *data)
{
	int height = 5 * PIXELS;
	int width = 6 * PIXELS;

    void *mlx = mlx_init(width, height, "Map Viewer", true);

	mlx_image_t* img = mlx_new_image(mlx, 1920, 1080);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return (error_msg("new_image"));

    draw_2d_map(data, img);

	mlx_loop_hook(mlx, &ft_hook, data);
	mlx_loop(mlx);

    return (true);
}
