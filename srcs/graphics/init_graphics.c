#include <graphics.h>

bool	init_graphics(t_general_data *data, t_graphics *graphics)
{
	graphics->width = data->file_data->map_data->col * PIXELS;
	graphics->height = (data->file_data->map_data->row * PIXELS) + PIXELS;

	graphics->mlx = mlx_init(graphics->width * 2, graphics->height * 2, "2D Map Viewer", true);
	// graphics->mlx = mlx_init(2048, 1020, "2D Map Viewer", true);
	// graphics->mlx = NULL; // ? testing
	if (!graphics->mlx)
		return (error_msg("mlx_init"));

	// graphics->mlx_3d = mlx_init(graphics->width, graphics->height, "3D Viewer", true);
	// if (!graphics->mlx_3d)
	// 	return (error_msg("mlx_3d_init"));
	
	graphics->img = mlx_new_image(graphics->mlx, graphics->width, graphics->height);
	// graphics->img = mlx_new_image(graphics->mlx, 500, 500);
	// graphics->img = NULL; // ? testing
	if (!graphics->img)
	{
		mlx_terminate(graphics->mlx);
		return (error_msg("mlx_new_image"));
	}

	graphics->img_3d = mlx_new_image(graphics->mlx, 500, 500);
	if (!graphics->img_3d)
	{
		mlx_terminate(graphics->mlx);
		return (error_msg("mlx_new_image 3d"));
	}
	return (true);
}
