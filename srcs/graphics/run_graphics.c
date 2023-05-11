#include <cub3D.h>

static bool	init_graphic_structs(t_general_data *data)
{
	if (!init_graphics(data))
		return (error_msg("init_graphics"));
	if (!init_textures(data))
		return (error_msg("init_textures"));
	// if (!init_dda(data))
	// 	return (error_msg("init_dda"));
	init_dda(data);
	if (!init_calc(data))
		return (error_msg("init_calc"));
	return (true);
}

bool	run_graphics(t_general_data *data)
{
	if (!init_graphic_structs(data))
		return (error_msg("init_graphics"));
	if (!fill_map(data))
		return (error_msg("Filling map"));
	if ((mlx_image_to_window(data->graphics.mlx, \
		data->graphics.img_3d, 0, 0) < 0))
		return (error_msg("mlx_image_to_window 3D"));
	mlx_loop_hook(data->graphics.mlx, &captain, data);
	mlx_loop(data->graphics.mlx);
	mlx_terminate(data->graphics.mlx);
	return (true);
}

/**
 * ? Display 2D map
*/
// bool	run_graphics(t_general_data *data)
// {
// 	if (!init_graphics(data))
// 		return (error_msg("init_graphics"));
// 	if (!init_textures(data))
// 		return (error_msg("init_textures"));
// 	if (!init_dda(data))
// 		return (error_msg("init_dda"));
// 	if (!init_calc(data))
// 		return (error_msg("init_calc"));
// 	if (!fill_map(data))
// 		return (error_msg("Filling map"));
// 	if (!fill_dda_data(data))
// 		return (error_msg("Filling dda data"));
// 	data->graphics.init_dir = false;
// 	if (!draw_2d_map(data))
// 		return (error_msg("Drawing 2D map"));
// 	if ((mlx_image_to_window(data->graphics.mlx, \?
// 		data->graphics.img_3d, 0, 0) < 0))
// 		return (error_msg("mlx_image_to_window 3D"));
// 	if ((mlx_image_to_window(data->graphics.mlx, data->graphics.img, 0, \?
// 		data->graphics.height - data->graphics.height / 2.25) < 0))
// 		return (error_msg("mlx_image_to_window 2D"));
// 	mlx_loop_hook(data->graphics.mlx, &captain, data);
// 	mlx_loop(data->graphics.mlx);
// 	mlx_terminate(data->graphics.mlx);
// 	return (true);
// }
