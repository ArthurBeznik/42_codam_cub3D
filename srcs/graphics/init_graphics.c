#include <cub3D.h>

bool	init_graphics(t_general_data *data)
{
	t_graphics	*graph;
	t_file_data	*file;

	graph = &data->graphics;
	file = &data->file_data;
	graph->width = 960;
	graph->height = 720;
	graph->mlx = mlx_init(graph->width, graph->height, "cub3D", false);
	if (!graph->mlx)
		return (error_msg("mlx_init"));
	graph->img = mlx_new_image(graph->mlx, graph->width, graph->height);
	if (!graph->img)
	{
		mlx_terminate(graph->mlx);
		return (error_msg("mlx_new_image"));
	}
	graph->img_3d = mlx_new_image(graph->mlx, graph->width, graph->height);
	if (!graph->img_3d)
	{
		mlx_terminate(graph->mlx);
		return (error_msg("mlx_new_image 3D"));
	}
	return (true);
}
