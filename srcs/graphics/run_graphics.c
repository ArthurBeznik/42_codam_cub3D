#include <graphics.h>

bool	fill_dda_data(t_general_data *data)
{
	t_dda *dda;

	dda = data->graphics->dda;
		// FOV = (2 * atan(0.66 / 1.0) = 66 deg)
		
	dda->dir_x = 0;
	dda->dir_y = -1;
	dda->plane_x = 0.66;
	dda->plane_y = 0; // the 2d raycaster version of camera plane
	// dda->w = data->graphics->width / PIXELS;
	// dda->h = data->graphics->height / PIXELS;
	dda->w = data->graphics->width;
	dda->h = data->graphics->height;
	dda->pos_x = data->file_data->player->px;
	dda->pos_y = data->file_data->player->py;
	return (true);
}

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

	if (!init_dda(data))
		return (error_msg("init_dda"));

	if (!fill_map(data))
		return (error_msg("Filling map"));

	if (!fill_dda_data(data))
		return (error_msg("Filling dda data"));

	data->graphics->init_dir = false;
	if (!draw_2d_map(data))
		return (error_msg("Drawing 2D map"));

	if ((mlx_image_to_window(data->graphics->mlx, data->graphics->img, 0, 0) < 0))
		return (error_msg("mlx_image_to_window"));

	if ((mlx_image_to_window(data->graphics->mlx, data->graphics->img_3d, data->graphics->width + 30, 0) < 0))
		return (error_msg("mlx_image_to_window 3D"));

	mlx_loop_hook(data->graphics->mlx, &captain, data);

	mlx_loop(data->graphics->mlx);

	mlx_terminate(data->graphics->mlx);
	return (true);
}
