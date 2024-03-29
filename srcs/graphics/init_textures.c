#include <cub3D.h>

static bool	load_textures(t_textures *textures, t_identifiers_data *id)
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
		return (error_msg("Loading textures"));
	}
	return (true);
}

static bool	check_texture_paths(t_identifiers_data *id)
{
	int	fd;

	fd = open(id->path_to_north_texture, O_RDONLY);
	if (fd == -1)
		return (error_msg("Reading north texture path"));
	close(fd);
	fd = open(id->path_to_south_texture, O_RDONLY);
	if (fd == -1)
		return (error_msg("Reading south texture path"));
	close(fd);
	fd = open(id->path_to_west_texture, O_RDONLY);
	if (fd == -1)
		return (error_msg("Reading west texture path"));
	close(fd);
	fd = open(id->path_to_east_texture, O_RDONLY);
	if (fd == -1)
		return (error_msg("Reading east texture path"));
	close(fd);
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
	if (!check_texture_paths(id))
	{
		free_data(data);
		terminate(&data->graphics, EXIT_FAILURE);
		return (false);
	}
	if (!load_textures(textures, id))
	{
		free_data(data);
		terminate(&data->graphics, EXIT_FAILURE);
		return (false);
	}
	return (true);
}
