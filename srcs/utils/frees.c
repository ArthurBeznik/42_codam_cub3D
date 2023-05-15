#include <cub3D.h>

void	set_all_null(t_general_data *data)
{
	data->file_data.identifiers.path_to_north_texture = NULL;
	data->file_data.identifiers.path_to_south_texture = NULL;
	data->file_data.identifiers.path_to_west_texture = NULL;
	data->file_data.identifiers.path_to_east_texture = NULL;
	data->graphics.textures.north_tex = NULL;
	data->graphics.textures.south_tex = NULL;
	data->graphics.textures.west_tex = NULL;
	data->graphics.textures.east_tex = NULL;
	data->file_data.scene = NULL;
	data->file_data.map_data.map = NULL;
	data->file_data.map_data.copy = NULL;
	data->file_data.line = NULL;
}

void	free_2d(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i] != NULL)
			free(array[i]);
		i++;
	}
	free(array);
	return ;
}

void	free_data(t_general_data *data)
{
	if (data->file_data.identifiers.path_to_north_texture != NULL)
		free(data->file_data.identifiers.path_to_north_texture);
	if (data->file_data.identifiers.path_to_south_texture != NULL)
		free(data->file_data.identifiers.path_to_south_texture);
	if (data->file_data.identifiers.path_to_west_texture != NULL)
		free(data->file_data.identifiers.path_to_west_texture);
	if (data->file_data.identifiers.path_to_east_texture != NULL)
		free(data->file_data.identifiers.path_to_east_texture);
	if (data->file_data.scene != NULL)
		free_2d(data->file_data.scene);
	if (data->file_data.map_data.map != NULL)
		free_2d(data->file_data.map_data.map);
	if (data->file_data.map_data.copy != NULL)
		free_2d(data->file_data.map_data.copy);
	if (data->file_data.line != NULL)
		free(data->file_data.line);
	set_all_null(data);
}
