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

void	log_positions(t_general_data *data, char player_or_image, char *message)
{
	if (player_or_image == 'I')
	{
		if (message)
			fprintf(stderr, "[%s] ix: %d | iy: %d\n", message, data->graphics->images[PLAYER]->instances[0].x, data->graphics->images[PLAYER]->instances[0].y);
		else
			fprintf(stderr, "ix: %d | iy: %d\n", data->graphics->images[PLAYER]->instances[0].x, data->graphics->images[PLAYER]->instances[0].y);
	}
	else if (player_or_image == 'P')
	{
		if (message)
			fprintf(stderr, "[%s] px: %lld | py: %lld\n", message, data->file_data->player->x, data->file_data->player->y);
		else
			fprintf(stderr, "px: %lld | py: %lld\n", data->file_data->player->x, data->file_data->player->y);
	}
}