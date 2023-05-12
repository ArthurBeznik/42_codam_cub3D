#include <cub3D.h>

int	check_texture_paths(t_identifiers_data *id)
{
	int	fd;

	fd = open(id->path_to_north_texture, O_RDONLY);
	if (fd == -1 || access(id->path_to_north_texture, F_OK) == -1)
		return (error_msg("Can't read North texture path"));
	close(fd);
	fd = open(id->path_to_south_texture, O_RDONLY);
	if (fd == -1 || access(id->path_to_south_texture, F_OK) == -1)
		return (error_msg("Can't read South texture path"));
	close(fd);
	fd = open(id->path_to_west_texture, O_RDONLY);
	if (fd == -1 || access(id->path_to_west_texture, F_OK) == -1)
		return (error_msg("Can't read West texture path"));
	close(fd);
	fd = open(id->path_to_east_texture, O_RDONLY);
	if (fd == -1 || access(id->path_to_east_texture, F_OK) == -1)
		return (error_msg("Can't read East texture path"));
	close(fd);
	return (true);
}

int	load_textures(t_textures *textures, t_identifiers_data *id)
{
	textures->north_tex = mlx_load_png(id->path_to_north_texture);
	textures->west_tex = mlx_load_png(id->path_to_west_texture);
	textures->south_tex = mlx_load_png(id->path_to_south_texture);
	textures->east_tex = mlx_load_png(id->path_to_east_texture);
	if (!textures->north_tex || !textures->west_tex || \
		!textures->south_tex || !textures->east_tex)
	{
		if (textures->north_tex != NULL)
			mlx_delete_texture(textures->north_tex);
		if (textures->south_tex != NULL)
			mlx_delete_texture(textures->south_tex);
		if (textures->west_tex != NULL)
			mlx_delete_texture(textures->west_tex);
		if (textures->east_tex != NULL)
			mlx_delete_texture(textures->east_tex);
		return (error_msg("Can't load textures"));
	}
	return (true);
}

bool	init_dda(t_general_data *data)
{
	data->graphics.dda.camera_x = NA;
	data->graphics.dda.delta_dist_x = NA;
	data->graphics.dda.delta_dist_y = NA;
	data->graphics.dda.dir_x = NA;
	data->graphics.dda.dir_y = NA;
	data->graphics.dda.h = NA;
	data->graphics.dda.hit = NA;
	data->graphics.dda.map_x = NA;
	data->graphics.dda.map_y = NA;
	data->graphics.dda.perp_wall_dist = NA;
	data->graphics.dda.plane_x = NA;
	data->graphics.dda.plane_y = NA;
	data->graphics.dda.player_x = NA;
	data->graphics.dda.player_y = NA;
	data->graphics.dda.pos_x = NA;
	data->graphics.dda.pos_y = NA;
	data->graphics.dda.ray_dir_x = NA;
	data->graphics.dda.ray_dir_y = NA;
	data->graphics.dda.side = NA;
	data->graphics.dda.side_dist_x = NA;
	data->graphics.dda.side_dist_y = NA;
	data->graphics.dda.step_x = NA;
	data->graphics.dda.step_y = NA;
	data->graphics.dda.w = NA;
	return (true);
}

bool	init_textures(t_general_data *data)
{
	t_textures			*textures;
	t_identifiers_data	*id;

	textures = &data->graphics.textures;
	id = &data->file_data.identifiers;
	textures->north_tex = NULL;
	textures->west_tex = NULL;
	textures->south_tex = NULL;
	textures->east_tex = NULL;
	textures->rgba = NA;
	if (check_texture_paths(id) == false)
	{
		free_data(data);
		terminate(&data->graphics);
		return (false);
	}
	if (load_textures(textures, id) == false)
	{
		free_data(data);
		terminate(&data->graphics);
		return (false);
	}
	return (true);
}

bool	init_graphics(t_general_data *data)
{
	t_graphics	*graph;
	t_file_data	*file;

	graph = &data->graphics;
	file = &data->file_data;
	graph->width = file->map_data.col * PIXELS;
	graph->height = (file->map_data.row * PIXELS) + PIXELS;
	graph->mlx = mlx_init(graph->width * 2.5, \
					graph->height * 1.5, "cub3D", true);
	if (!graph->mlx)
		return (error_msg("mlx_init"));
	graph->img = mlx_new_image(graph->mlx, graph->width, graph->height);
	if (!graph->img)
	{
		mlx_terminate(graph->mlx);
		return (error_msg("mlx_new_image"));
	}
	graph->img_3d = mlx_new_image(graph->mlx, graph->width, graph->height);
	if (!graph->img_3d)
	{
		mlx_terminate(graph->mlx);
		return (error_msg("mlx_new_image 3D"));
	}
	return (true);
}
