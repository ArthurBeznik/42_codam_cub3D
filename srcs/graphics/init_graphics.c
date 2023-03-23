#include <graphics.h>

bool	init_graphics(t_general_data *data, t_graphics *graphics)
{
	// ? init W and H
	graphics->width = data->file_data->map_data->max_line_len * PIXELS;
	graphics->height = (data->file_data->map_data->rows_count * PIXELS) + PIXELS;

	// ? mlx init
	graphics->mlx = mlx_init(graphics->width, graphics->height, "2D Map Viewer", true);
	if (!graphics->mlx)
		return (error_msg("mlx_init"));
	
	// ? new image
	graphics->img = mlx_new_image(graphics->mlx, graphics->width, graphics->height);
	if (!graphics->img)
		return (error_msg("mlx_new_image"));

	// ? draw 2D map
	graphics->init_dir = false;
	draw_2d_map(data, data->graphics->img);
		// ? check direction, compute angle and delta x & y
		// ? draw player
		// ? draw direction

	// ? mlx image to window
	if ((mlx_image_to_window(data->graphics->mlx, data->graphics->img, 0, 0) < 0))
		return (error_msg("mlx_image_to_window"));

	// ? return
	return (true);
}
