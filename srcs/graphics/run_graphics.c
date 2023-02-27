#include <graphics.h>

bool	run_graphics(t_graphics *graphics)
{
	if (!init_graphics(graphics))
		return (false);
	mlx_loop(graphics->mlx);
	return (true);
}
