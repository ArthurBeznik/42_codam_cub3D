#include <cub3D.h>
#include <graphics.h>

// TESTING LEAKS
void	check(void)
{
	system("leaks cub3D");
}

int	main(int argc, char *argv[])
{
	t_general_data	data;

	atexit(&check);
	if (!parser(argc, argv, &data))
	{
		free_data(&data); // ! this is causing one of the malloc errors
		return (1);
	}
	if (!run_graphics(&data))
		free_data(&data);
	free_data(&data);
	return (0);
}
