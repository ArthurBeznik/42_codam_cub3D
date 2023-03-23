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
	// fprintf(stderr, "%d\n", data->graphics->init_dir);

	// ? mlx loop hook
	mlx_loop_hook(data->graphics->mlx, &captain, data);

	// ? mlx loop
	mlx_loop(data->graphics->mlx);

	// ? mlx terminate
	mlx_terminate(data->graphics->mlx);
	return (true);
}
