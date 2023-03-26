#include <graphics.h>

void	terminate(t_graphics *graphics)
{
	mlx_close_window(graphics->mlx);
	mlx_terminate(graphics->mlx);
	exit(0);
}

void	free_close_window(t_graphics *graphics, void *var, char *str)
{
	ft_putendl_fd("Error\n", STDOUT_FILENO);
	ft_putendl_fd(str, STDOUT_FILENO);
	free(var);
	terminate(graphics);
}

void	log_positions(t_general_data *data, char *function, char values)
{
	if (values == 'D')
		fprintf(stderr, "[%s]\tdx | dy\t\t%f | %f\n", function, data->file_data->player->dx, data->file_data->player->dy);
	if (values == 'A')
		fprintf(stderr, "[%s]\tangle\t\t%f\n", function, data->file_data->player->angle);
	if (values == 'P')
		fprintf(stderr, "[%s]\tpx | py\t\t%f | %f\n", function, data->file_data->player->x / PIXELS, data->file_data->player->y / PIXELS);
	// if (values == '1')
	// 	fprintf(stderr, "[%s]\tx1 | y1\t\t%f | %f\n", function, data->file_data->player->dx, data->file_data->player->dy);

}

bool	check_put_pixel(t_general_data *data, uint32_t x, uint32_t y)
{
	if (x >= data->graphics->width || x < 0)
		return (error_msg("Invalid x"));
	if (y >= data->graphics->height || y < 0)
		return (error_msg("Invalid y"));
	return (true);
}