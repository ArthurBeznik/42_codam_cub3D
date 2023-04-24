#include <graphics.h>

bool	init_dda(t_general_data *data)
{
	t_dda	*dda;

	dda = (t_dda *)malloc(sizeof(t_dda));
	if (!dda)
		return (error_msg("Malloc dda struct"));
	dda->camera_x = NA;
	dda->delta_dist_x = NA;
	dda->delta_dist_y = NA;
	dda->dir_x = NA;
	dda->dir_y = NA;
	dda->h = NA;
	dda->hit = NA;
	dda->map_x = NA;
	dda->map_y = NA;
	dda->perp_wall_dist = NA;
	dda->plane_x = NA;
	dda->plane_y = NA;
	dda->player_x = NA;
	dda->player_y = NA;
	dda->pos_x = NA;
	dda->pos_y = NA;
	dda->ray_dir_x = NA;
	dda->ray_dir_y = NA;
	dda->side = NA;
	dda->side_dist_x = NA;
	dda->side_dist_y = NA;
	dda->step_x = NA;
	dda->step_y = NA;
	dda->w = NA;
	data->graphics->dda = dda;
	return (true);
}

bool	init_textures(t_general_data *data)
{
	t_textures *textures;

	textures = (t_textures *)malloc(sizeof(t_textures));
	if (!textures)
		return (error_msg("Malloc textures struct"));
	textures->north_tex = NULL;
	textures->west_tex = NULL;
	textures->south_tex = NULL;
	textures->east_tex = NULL;
	textures->rgba = NA;
	textures->north_tex = mlx_load_png(data->file_data.identifiers->path_to_north_texture);
	textures->west_tex = mlx_load_png(data->file_data.identifiers->path_to_west_texture);
	textures->south_tex = mlx_load_png(data->file_data.identifiers->path_to_south_texture);
	textures->east_tex = mlx_load_png(data->file_data.identifiers->path_to_east_texture);
	if (!textures->north_tex || !textures->west_tex || !textures->south_tex || !textures->east_tex)
		return (error_msg("mlx_load_png"));
	// fprintf(stderr, "path: %s\n", data->file_data.identifiers->path_to_north_texture); // ? testing
	// fprintf(stderr, "path: %s\n", data->file_data.identifiers->path_to_south_texture); // ? testing
	// fprintf(stderr, "path: %s\n", data->file_data.identifiers->path_to_east_texture); // ? testing
	// fprintf(stderr, "path: %s\n", data->file_data.identifiers->path_to_west_texture); // ? testing
	data->graphics->textures = textures;
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
