#include <cub3D.h>
#include "../includes/graphics.h"

// TESTING LEAKS
void	check(void)
{
	system("leaks cub3D");
}

int	main(int argc, char *argv[])
{
	atexit(&check);
	t_general_data	data;
	data.free_data = false;
	// t_file_data		file_data;
	// t_graphics	graphics;

	if (!parser(argc, argv, &data))
	{
		if (data.free_data)
			free_data(&data, true);
		return (1);
	}
  	if (!run_graphics(&data))
	{
		free_data(&data, true);
		terminate(data.graphics);
	}
	free_2d(data.file_data->map_data->map);
	free(data.file_data->identifiers->path_to_north_texture);
	free(data.file_data->identifiers->path_to_south_texture);
	free(data.file_data->identifiers->path_to_west_texture);
	free(data.file_data->identifiers->path_to_east_texture);
	free(data.file_data->identifiers);
	free(data.file_data->player);
	free(data.file_data->map_data);
	free(data.file_data);
	// free_data(&data, false);
	// free(file_data.line);
	// system("leaks cub3D");
	return (0);
}
