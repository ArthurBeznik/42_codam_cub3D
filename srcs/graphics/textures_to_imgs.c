#include <graphics.h>

bool	texture_to_image(t_graphics *graphics, mlx_texture_t **textures, \
													mlx_image_t **image)
{
	image[BG] = mlx_texture_to_image(graphics->mlx, textures[BG]);
	image[PLAYER] = mlx_texture_to_image(graphics->mlx, textures[PLAYER]);
	image[WALL] = mlx_texture_to_image(graphics->mlx, textures[WALL]);
	if (!image[BG] || !image[PLAYER] || !image[WALL])
		return (false);
	return (true);
}
