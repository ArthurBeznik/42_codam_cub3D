#include <graphics.h>

bool	init_graphics(t_general_data *data, t_graphics *graphics)
{
	graphics->width = data->file_data->map_data->col * PIXELS;
	graphics->height = (data->file_data->map_data->row * PIXELS) + PIXELS;

	graphics->mlx = mlx_init(graphics->width, graphics->height, "2D Map Viewer", true);
	// graphics->mlx = NULL; // ? testing
	if (!graphics->mlx)
		return (error_msg("mlx_init"));
	
	graphics->img = mlx_new_image(graphics->mlx, graphics->width, graphics->height);
	// graphics->img = NULL; // ? testing
	if (!graphics->img)
	{
		mlx_terminate(graphics->mlx);
		return (error_msg("mlx_new_image"));
	}

	return (true);
}
