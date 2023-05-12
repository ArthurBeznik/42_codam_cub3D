#include <cub3D.h>

void	terminate(t_graphics *graphics)
{
	mlx_delete_image(graphics->mlx, graphics->img);
	mlx_close_window(graphics->mlx);
	mlx_terminate(graphics->mlx);
	exit(0);
}

/**
 * do you still need this?
*/
void	free_close_window(t_graphics *graphics, void *var, char *str)
{
	ft_putendl_fd("Error\n", STDOUT_FILENO);
	ft_putendl_fd(str, STDOUT_FILENO);
	free(var);
	terminate(graphics);
}

bool	check_put_pixel(t_general_data *data, uint32_t x, uint32_t y)
{
	if (x > data->graphics.width || x < 0)
		return (error_msg("Invalid x"));
	if (y > data->graphics.height || y < 0)
		return (error_msg("Invalid y"));
	return (true);
}
