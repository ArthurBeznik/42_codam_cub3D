#include <cub3D.h>
#include "../includes/graphics.h"

int	main(int argc, char *argv[])
{
	t_general_data	data;
	t_file_data		file_data;
  t_graphics	graphics;

	if (!parser(argc, argv, &file_data))
		return (1);
  if (!run_graphics(&graphics))
		return (1);
	free(file_data.line);
	// system("leaks cub3D");
	return (0);
}
