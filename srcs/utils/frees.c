#include <cub3D.h>

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

void	free_data(t_general_data *data, bool free_map)
{
	if (free_map)
	{
		free(data->file_data.identifiers->path_to_north_texture);
		free(data->file_data.identifiers->path_to_south_texture);
		free(data->file_data.identifiers->path_to_west_texture);
		free(data->file_data.identifiers->path_to_east_texture);
		free_2d(data->file_data.map_data.map);
		free_2d(data->file_data.map_data.copy);
		free(data->file_data.line);
	}
	if (data->file_data.identifiers)
		free(data->file_data.identifiers);
	if (data->file_data.player)
		free(data->file_data.player);
	// if (data->file_data.map_data)
	// 	free(data->file_data.map_data);
	// if (data->file_data)
	// 	free(data->file_data);
}
