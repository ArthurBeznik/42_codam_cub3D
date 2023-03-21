#include <graphics.h>

bool	run_graphics(t_general_data	*data)
{
	t_graphics graphics;

	data->graphics = &graphics;
	if (!init_graphics(data, data->graphics))
	{
		error_msg("init_graphics failed");
		return (terminate(data->graphics), false);
	}
	mlx_loop_hook(data->graphics->mlx, &ft_hook, data); // ? crashes if this is uncommented
	mlx_loop(data->graphics->mlx); // ? crashes here as well
	return (true);
}
