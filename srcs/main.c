
#include "../includes/graphics.h"

int	main(int argc, char *argv[])
{
	t_graphics	graphics;

	(void)argc;
	(void)argv;
	if (!run_graphics(&graphics))
		return (1);
	return (0);
}
