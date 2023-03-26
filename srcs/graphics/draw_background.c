#include <graphics.h>

bool	draw_background(t_graphics *graphics)
{
	// int	x;
	// int	y;
	// int	color;

	// y = 0;
	// color = 0x000000;
	// // if (!init_mlx(graphics))
	// 	// return (false);
	// while (y < HEIGHT)
	// {
	// 	x = 0;
	// 	while (x < WIDTH)
	// 	{
	// 		mlx_image_to_window(graphics->mlx, graphics->img, \
	// 			x * PIXELS, y * PIXELS);
	// 		if (!mlx_image_to_window(graphics->mlx, \
	// 			graphics->img, x * PIXELS, y * PIXELS))
	// 			return (false);
	// 		x++;
	// 	}
	// 	y++;
	// }
	fprintf(stderr, "[norm] %lld| %lld\n", graphics->width, graphics->height);
	return (true);
}
