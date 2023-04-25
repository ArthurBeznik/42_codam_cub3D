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

void	free_data(t_general_data *data)
{
	free(data->file_data.identifiers.path_to_north_texture);
	free(data->file_data.identifiers.path_to_south_texture);
	free(data->file_data.identifiers.path_to_west_texture);
	free(data->file_data.identifiers.path_to_east_texture);
	if (data->file_data.scene != NULL)
		free_2d(data->file_data.scene);
	if (data->file_data.map_data.map != NULL)
	{
		fprintf(stderr, "FREEING MAP\n");
		free_2d(data->file_data.map_data.map);
		fprintf(stderr, "MAP FREED\n");
	}
	if (data->file_data.map_data.copy != NULL)
	{
		fprintf(stderr, "FREEING COPY\n");
		free_2d(data->file_data.map_data.copy);
		fprintf(stderr, "COPY FREED\n");
	}
	fprintf(stderr, "FREEING LINE\n");
	// if (data->file_data.line != NULL)
	free(data->file_data.line);
	fprintf(stderr, "LINE FREED\n");
}
