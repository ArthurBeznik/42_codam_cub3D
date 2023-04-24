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

	if (!parser(argc, argv, &data))
	{
		free_data(&data);
		return (1);
	}
  	if (!run_graphics(&data))
	{
		free_data(&data);
		terminate(data.graphics);
	}
	free_2d(data.file_data.map_data.map);
	free(data.file_data.identifiers.path_to_north_texture);
	free(data.file_data.identifiers.path_to_south_texture);
	free(data.file_data.identifiers.path_to_west_texture);
	free(data.file_data.identifiers.path_to_east_texture);
	return (0);
}
