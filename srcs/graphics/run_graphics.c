#include <graphics.h>

bool	run_graphics(t_general_data	*data)
{
	t_graphics	graphics;

	data->graphics = &graphics;
	if (!init_graphics(data, data->graphics))
		return (error_msg("init_graphics"));

	if (!init_rays(data))
		return (error_msg("init_rays"));

	if (!init_textures(data))
		return (error_msg("init_textures"));

	if (!fill_map(data))
		return (error_msg("Filling map"));

	data->graphics->init_dir = false;
	if (!draw_2d_map(data))
		return (error_msg("Drawing 2D map"));

	if ((mlx_image_to_window(data->graphics->mlx, data->graphics->img, 0, 0) < 0))
		return (error_msg("mlx_image_to_window"));

	if ((mlx_image_to_window(data->graphics->mlx, data->graphics->img_3d, data->graphics->width, 0) < 0))
		return (error_msg("mlx_image_to_window 3D"));

	mlx_loop_hook(data->graphics->mlx, &captain, data);

	mlx_loop(data->graphics->mlx);

	mlx_terminate(data->graphics->mlx);
	return (true);
}
