#include <graphics.h>

bool	init_mlx(t_general_data	*data, t_graphics *graphics)
{
	graphics->mlx = mlx_init(graphics->width, graphics->height, "Cub3D", true);
	if (!graphics->mlx)
		return (false);
	graphics->textures[BG] = mlx_load_png(data->file_data->identifiers->path_to_east_texture);
	if (!graphics->textures[BG])
		return (false);
	graphics->images[BG] = mlx_texture_to_image(graphics->mlx, \
												graphics->textures[BG]);
	if (!graphics->images[BG])
		return (false);
	return (true);
}

bool	init_ray_mlx(t_general_data	*data, t_graphics *graphics)
{
	graphics->mlx = mlx_init(graphics->width, \
		graphics->height, "2D Map Viewer", true);
	if (!graphics->mlx)
		return (false);
	graphics->images[IMG_FLOOR] = mlx_new_image(graphics->mlx, \
		graphics->width, graphics->height);
	if (!graphics->images[IMG_FLOOR])
		return (false);
	graphics->images[PLAYER] = mlx_new_image(graphics->mlx, \
		data->graphics->width, graphics->height);
	if (!graphics->images[PLAYER])
		return (false);
	return (true);
}

bool	init_graphics(t_general_data *data, t_graphics *graphics)
{
	graphics->width = data->file_data->map_data->max_line_len * PIXELS;
	graphics->height = (data->file_data->map_data->rows_count * PIXELS) + PIXELS;
	// fprintf(stderr, "map width: %lld", data->file_data->map_data->max_line_len);
	// fprintf(stderr, " | map height: %lld\n", data->file_data->map_data->rows_count);
	// if (!init_mlx(data, graphics))
	// 	return (false);
	// if (!draw_background(graphics))
	// 	return (false);
	// if (mlx_image_to_window(graphics->mlx, graphics->images[BG], \
	// 										200, 200) == ERROR)
	// 	return (free_close_window(graphics, graphics->images[BG], \
	// 							"image_to_window failed"), false);
	// mlx_set_instance_depth(graphics->images[BG]->instances, -999);
	if (!init_ray_mlx(data, graphics))
		return (false);
	if (!map_viewer(data))
		return (false);
	if (!ray_caster(data))
		return (false);
	return (true);
}
