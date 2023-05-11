#include <cub3D.h>

bool	init_calc(t_general_data *data)
{
	data->graphics.calc.line_height = NA;
	data->graphics.calc.pitch = NA;
	data->graphics.calc.draw_start = NA;
	data->graphics.calc.draw_end = NA;
	data->graphics.calc.hit = NA;
	data->graphics.calc.wall_x = NA;
	data->graphics.calc.tex_x = NA;
	data->graphics.calc.tex_y = NA;
	data->graphics.calc.tex_pos = NA;
	data->graphics.calc.step = NA;
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
	graph->width = 960;
	graph->height = 720;
	graph->mlx = mlx_init(graph->width, graph->height, "cub3D", true);
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
