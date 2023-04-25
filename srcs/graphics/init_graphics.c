#include <graphics.h>

bool	init_dda(t_general_data *data)
{
	data->graphics->dda.camera_x = NA;
	data->graphics->dda.delta_dist_x = NA;
	data->graphics->dda.delta_dist_y = NA;
	data->graphics->dda.dir_x = NA;
	data->graphics->dda.dir_y = NA;
	data->graphics->dda.h = NA;
	data->graphics->dda.hit = NA;
	data->graphics->dda.map_x = NA;
	data->graphics->dda.map_y = NA;
	data->graphics->dda.perp_wall_dist = NA;
	data->graphics->dda.plane_x = NA;
	data->graphics->dda.plane_y = NA;
	data->graphics->dda.player_x = NA;
	data->graphics->dda.player_y = NA;
	data->graphics->dda.pos_x = NA;
	data->graphics->dda.pos_y = NA;
	data->graphics->dda.ray_dir_x = NA;
	data->graphics->dda.ray_dir_y = NA;
	data->graphics->dda.side = NA;
	data->graphics->dda.side_dist_x = NA;
	data->graphics->dda.side_dist_y = NA;
	data->graphics->dda.step_x = NA;
	data->graphics->dda.step_y = NA;
	data->graphics->dda.w = NA;
	return (true);
}

bool	init_textures(t_general_data *data)
{
	data->graphics->textures.north_tex = NULL;
	data->graphics->textures.west_tex = NULL;
	data->graphics->textures.south_tex = NULL;
	data->graphics->textures.east_tex = NULL;
	data->graphics->textures.rgba = NA;
	data->graphics->textures.north_tex = mlx_load_png(data->file_data.identifiers.path_to_north_texture);
	data->graphics->textures.west_tex = mlx_load_png(data->file_data.identifiers.path_to_west_texture);
	data->graphics->textures.south_tex = mlx_load_png(data->file_data.identifiers.path_to_south_texture);
	data->graphics->textures.east_tex = mlx_load_png(data->file_data.identifiers.path_to_east_texture);
	if (!data->graphics->textures.north_tex || !data->graphics->textures.west_tex || \
		!data->graphics->textures.south_tex || !data->graphics->textures.east_tex)
		return (error_msg("mlx_load_png"));
	return (true);
}

bool	init_graphics(t_general_data *data, t_graphics *graphics)
{
	graphics->width = data->file_data.map_data.col * PIXELS;
	graphics->height = (data->file_data.map_data.row * PIXELS) + PIXELS;

	graphics->mlx = mlx_init(graphics->width * 2.5, graphics->height * 1.5, "cub3D", true);
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

	// graphics->img_3d = mlx_new_image(graphics->mlx, 500, 500);
	graphics->img_3d = mlx_new_image(graphics->mlx, graphics->width, graphics->height);
	// graphics->img_3d = NULL; // ? testing
	if (!graphics->img_3d)
	{
		mlx_terminate(graphics->mlx);
		return (error_msg("mlx_new_image 3D"));
	}
	return (true);
}
