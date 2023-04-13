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
		terminate(data.graphics);
	// free(file_data.line);
	// system("leaks cub3D");
	return (0);
}
