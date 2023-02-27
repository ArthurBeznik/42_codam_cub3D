#include <graphics.h>

bool	run_graphics(t_general_data	*data, t_graphics *graphics)
{
	if (!init_graphics(data, graphics))
		return (false);
	mlx_loop_hook(graphics->mlx, &hook, data);
	mlx_loop(graphics->mlx);
	return (true);
}
