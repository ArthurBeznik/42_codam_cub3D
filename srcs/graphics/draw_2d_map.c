#include <graphics.h>

void ft_hook(void* param)
{
	t_general_data		*data;
	// size_t				x;
	// size_t				y;

	data = (t_general_data *)param;
	// x = (data->graphics->images[PLAYER]->instances[0].x / PIXELS);
	// y = (data->graphics->images[PLAYER]->instances[0].y / PIXELS);
	if (mlx_is_key_down(data->graphics->mlx, MLX_KEY_ESCAPE))
		terminate(data->graphics);
	// if (mlx_is_key_down(data->graphics->mlx, MLX_KEY_S) \
	// 					&& data->file_data->map_data->map[y + 1][x] != '1')
	// 		data->graphics->images[PLAYER]->instances[0].y += PIXELS;
	// else if (mlx_is_key_down(data->graphics->mlx, MLX_KEY_A) \
	// 					&& data->file_data->map_data->map[y][x - 1] != '1')
	// 		data->graphics->images[PLAYER]->instances[0].x -= PIXELS;
	// else if (mlx_is_key_down(data->graphics->mlx, MLX_KEY_D) \
	// 					&& data->file_data->map_data->map[y][x + 1] != '1')
	// 	data->graphics->images[PLAYER]->instances[0].x += PIXELS;
	// else if (mlx_is_key_down(data->graphics->mlx, MLX_KEY_W) \
	// 					&& data->file_data->map_data->map[y - 1][x] != '1')
	// 	data->graphics->images[PLAYER]->instances[0].y -= PIXELS;
	// printf("WIDTH: %d | HEIGHT: %d\n", WIDTH, HEIGHT);
}

static void draw_h_line(t_graphics *graphics, int x, int y, int size, int color)
{
    int	i;

    for (i = 0; i < size; i++)
	{
			fprintf(stderr, "x: %d | y: %d\n", x, y);
            mlx_put_pixel(graphics->images[LINE], x + i, y, color);
    }
}

// static void draw_v_line(t_graphics *graphics, int x, int y, int size, int color)
// {
//     int	i;

//     for (i = 0; i < size; i++)
// 	{
// 			fprintf(stderr, "x: %d | y: %d\n", x, y);
//             mlx_put_pixel(graphics->images[LINE], x, y + i, color);
//     }
// }

static void draw_square(t_graphics *graphics, int x, int y, int size, int color)
{
    int	i;
	int	j;

    for (i = 0; i < size; i++)
	{
        for (j = 0; j < size; j++)
		{
			// fprintf(stderr, "x: %d | y: %d\n", j, i);
            mlx_put_pixel(graphics->images[WALL], x + i, y + j, color);
        }
    }
}

// static void	draw_circle(t_graphics *graphics, int x, int y, int radius, int color)
// {
// 	int		i;
// 	int		j;

// 	i = -radius;
// 	while (i <= radius)
// 	{
// 		j = -radius;
// 		while (j <= radius)
// 		{
// 			if (i*i + j*j <= radius * radius)
// 				mlx_put_pixel(graphics->images[PLAYER], x+i, y+j, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// Function to draw the map and grid
static void draw_2d_map(t_general_data *data, t_graphics *graphics)
{
    int	y; 
	int	x;

    for (y = 0; y < 5; y++)
	{
        for (x = 0; x < 6; x++)
		{
            if (data->file_data->map_data->map[y][x] == '1')
			{
                // Draw black square for 1
                draw_square(graphics, x * PIXELS, y * PIXELS, PIXELS, 255);
            }
		// 	// else if (data->file_data->map_data->map[y][x] == 'S')
		// 	// {
		// 	// 	// Draw dot for player
		// 	// 	draw_circle(graphics, x * PIXELS + 32, y * PIXELS + 32, 8, 255);
        //     // }
		// 	// else
		// 	// {
        //     //     // Draw white square for 0
        //     //     draw_square(graphics, x * PIXELS, y * PIXELS, PIXELS, 0);
        //     // }
        }
    }

    // Draw grid lines
	for (y = 0; y < 5; y++)
	{
        for (x = 0; x < 6; x++)
		{
			fprintf(stderr, "x: %d | y: %d | %c\n", x, y, data->file_data->map_data->map[y][x]);
			// mlx_put_pixel(graphics->images[LINE], x, y, 255);
			draw_h_line(graphics, x * PIXELS, y * PIXELS, PIXELS, 0);
			// draw_v_line(graphics, x * PIXELS, y * PIXELS, PIXELS, 255);
        }
    }
}

bool draw_map(t_general_data *data, int64_t width, int64_t height)
{
	data->graphics->mlx = mlx_init(width, height, "Map Viewer", true);
    // void *mlx = mlx_init(width, height, "Map Viewer", true);
	if (!data->graphics->mlx)
		return (error_msg("mlx_init"));
	data->graphics->images[PLAYER] = mlx_new_image(data->graphics->mlx, 64, 64);
	data->graphics->images[WALL] = mlx_new_image(data->graphics->mlx, 64, 64);
	data->graphics->images[LINE] = mlx_new_image(data->graphics->mlx, 64, 64);
	// if (!data->graphics->images[PLAYER])
	// 	return (error_msg("player_image"));
	// data->graphics->images[PLAYER]->instances[0].x = 20;
	// data->graphics->images[PLAYER]->instances[0].y = 25;
	if (mlx_image_to_window(data->graphics->mlx, data->graphics->images[PLAYER], 0, 0) < 0 \
		|| mlx_image_to_window(data->graphics->mlx, data->graphics->images[WALL], 0, 0) < 0 \
		|| mlx_image_to_window(data->graphics->mlx, data->graphics->images[LINE], 0, 0) < 0)
		return (error_msg("image_to_window"));
	// if (mlx_image_to_window(data->graphics->mlx, data->graphics->images[LINE], 0, 0) < 0)
		// return (error_msg("image_to_window"));
	// mlx_image_t* img = mlx_new_image(mlx, 1920, 1080);
	// if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	// 	return (error_msg("new_image"));

    draw_2d_map(data, data->graphics);
    return (true);
}
