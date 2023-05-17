#include <cub3D.h>

void	terminate_textures(t_general_data *data)
{
	if (data->graphics.textures.north_tex != NULL)
		mlx_delete_texture(data->graphics.textures.north_tex);
	if (data->graphics.textures.south_tex != NULL)
		mlx_delete_texture(data->graphics.textures.south_tex);
	if (data->graphics.textures.west_tex != NULL)
		mlx_delete_texture(data->graphics.textures.west_tex);
	if (data->graphics.textures.east_tex != NULL)
		mlx_delete_texture(data->graphics.textures.east_tex);
}

void	terminate(t_graphics *graphics, int code)
{
	mlx_delete_image(graphics->mlx, graphics->img_3d);
	mlx_close_window(graphics->mlx);
	mlx_terminate(graphics->mlx);
	exit(code);
}

bool	check_put_pixel(t_general_data *data, uint32_t x, uint32_t y)
{
	if (x > data->graphics.width || x < 0)
		return (error_msg("Invalid x"));
	if (y > data->graphics.height || y < 0)
		return (error_msg("Invalid y"));
	return (true);
}
