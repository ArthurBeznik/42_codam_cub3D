#include <graphics.h>

bool	init_textures(t_general_data *data)
{
	t_textures *textures;

	textures = (t_textures *)malloc(sizeof(t_textures));
	if (!textures)
		return (error_msg("Malloc textures struct"));
	textures->hmt = NA;
	textures->vmt = NA;
	textures->shade = NA;
	textures->x = NA;
	textures->y = NA;
	textures->y_off = NA;
	textures->y_step = NA;
	textures->north_tex = NULL;
	textures->west_tex = NULL;
	textures->south_tex = NULL;
	textures->east_tex = NULL;
	textures->rgba = NA;
	textures->north_tex = mlx_load_png(data->file_data->identifiers->path_to_north_texture);
	textures->west_tex = mlx_load_png(data->file_data->identifiers->path_to_west_texture);
	textures->south_tex = mlx_load_png(data->file_data->identifiers->path_to_south_texture);
	textures->east_tex = mlx_load_png(data->file_data->identifiers->path_to_east_texture);
	// fprintf(stderr, "path: %s\n", data->file_data->identifiers->path_to_north_texture);
	// fprintf(stderr, "path: %s\n", data->file_data->identifiers->path_to_south_texture);
	// fprintf(stderr, "path: %s\n", data->file_data->identifiers->path_to_east_texture);
	// fprintf(stderr, "path: %s\n", data->file_data->identifiers->path_to_west_texture);
	textures->floor.rgba = data->file_data->identifiers->floor.rgba;
	textures->floor.a = 255;
	textures->ceiling.rgba = data->file_data->identifiers->ceiling.rgba;
	textures->ceiling.a = 255;
	data->graphics->textures = textures;
	return (true);
}

bool	init_rays(t_general_data *data)
{
	int		i;
	t_ray	**ray;

	i = 0;
	ray = (t_ray **)malloc(sizeof(t_ray) * NB_RAYS);
	if (!ray)
		return (error_msg("Malloc ray struct"));
	while (i < NB_RAYS)
	{
		ray[i] = (t_ray *)malloc(sizeof(t_ray));
		if (!ray[i])
			// ! free ray
			return (error_msg("Malloc ray ptr"));
		ray[i]->x = NA;
		ray[i]->y = NA;
		ray[i]->angle = NA;
		ray[i]->off_x = NA;
		ray[i]->off_y = NA;
		ray[i]->hit_x = NA;
		ray[i]->hit_y = NA;
		ray[i]->vx = NA;
		ray[i]->vy = NA;
		ray[i]->dist_v = NA;
		ray[i]->dist_h = NA;
		ray[i]->tan_var = NA;
		ray[i]->dof = NA;
		i++;
	}
	data->graphics->ray = ray;
	return (true);
}

bool	init_graphics(t_general_data *data, t_graphics *graphics)
{
	graphics->width = data->file_data->map_data->col * PIXELS;
	graphics->height = (data->file_data->map_data->row * PIXELS) + PIXELS;

	graphics->mlx = mlx_init(graphics->width * 2, graphics->height, "cub3D", true);
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

	graphics->img_3d = mlx_new_image(graphics->mlx, 500, 500);
	// graphics->img_3d = NULL; // ? testing
	if (!graphics->img_3d)
	{
		mlx_terminate(graphics->mlx);
		return (error_msg("mlx_new_image 3D"));
	}
	return (true);
}
