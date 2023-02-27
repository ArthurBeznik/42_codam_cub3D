#include <graphics.h>

void	movement(t_graphics *graphics, size_t y, size_t x)
{
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_S) \
						&& graphics->map[y + 1][x] != '1')
			graphics->images[PLAYER]->instances[0].y += PIXELS;
	else if (mlx_is_key_down(graphics->mlx, MLX_KEY_A) \
							&& graphics->map[y][x - 1] != '1')
			graphics->images[PLAYER]->instances[0].x -= PIXELS;
	else if (mlx_is_key_down(graphics->mlx, MLX_KEY_D) \
							&& graphics->map[y][x + 1] != '1')
		graphics->images[PLAYER]->instances[0].x += PIXELS;
	else if (mlx_is_key_down(graphics->mlx, MLX_KEY_W) \
		&& graphics->map[y - 1][x] != '1')
		graphics->images[PLAYER]->instances[0].y -= PIXELS;
}

void	hook(void *param)
{
	size_t			x;
	size_t			y;
	t_graphics		*graphics2;

	graphics2 = (t_graphics *)param;
	x = (graphics2->images[PLAYER]->instances[0].x / PIXELS);
	y = (graphics2->images[PLAYER]->instances[0].y / PIXELS);
	if (mlx_is_key_down(graphics2->mlx, MLX_KEY_ESCAPE))
		terminate(graphics2);
	movement(graphics2, y, x);
}
