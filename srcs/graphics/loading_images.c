#include <graphics.h>

bool	loading_images(mlx_texture_t **textures)
{
	textures[WALL] = mlx_load_png("./textures/stone.png");
	if (!textures[WALL])
		return (error_msg("wall texture was not found"), false);
	textures[PLAYER] = mlx_load_png("./textures/diamond.png");
	if (!textures[PLAYER])
		return (error_msg("player texture was not found"), false);
	return (true);
}
