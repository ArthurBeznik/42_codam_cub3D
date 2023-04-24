#include <graphics.h>

bool	dda_draw_direction(t_general_data *data, mlx_image_t *img)
{
	int		i;
	float	x;
	float	y;
	float	step;
	float	dx;
	float	dy;
	float	x1;
	float	x2;
	float	y1;
	float	y2;

	/**
	 * A linear DDA starts by calculating the smaller of dy or dx for a unit increment of the other. 
	 * A line is then sampled at unit intervals in one coordinate and corresponding integer 
	 * values nearest the line path are determined for the other coordinate.
	*/
	x1 = data->file_data.player->x;
	y1 = data->file_data.player->y;
	x2 = data->file_data.player->x + (data->graphics->dda->dir_x * 16);
	y2 = data->file_data.player->y + (data->graphics->dda->dir_y * 16);
	dx = (x2 - x1);
	dy = (y2 - y1);
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	x = x1;
	y = y1;
	i = 1;
	while (i <= step)
	{
		mlx_put_pixel(img, x, y, RED);
		x += dx;
		y += dy;
		i++;
	}

	// fprintf(stderr, "dir_x | dir_y : %f | %f\n", data->graphics->dda->dir_x, data->graphics->dda->dir_y);
	// fprintf(stderr, "tmp_x | tmp_y : %d | %d\n", tmp_x, tmp_y);
	// fprintf(stderr, "px | py : %f | %f\n", data->file_data.player->x, data->file_data.player->y);

	return (true);
}

/**
 * TODO verifiy this is actually correct because once setting the size to 64
 * TODO the player goes over gridlines
 * x - p_size 
 * 		. x: center position of the square in pixels
 * 		. p_size: player size in pixels
 * 		. => gives us the starting x of the square to draw, same thing for y
 * we want to draw 
 * 	8 pixels left, 
 * 	8 pixels right, 
 * 	8 pixels up and 
 * 	8 pixels down 
 * 			of player x and y
*/
bool	draw_player(t_general_data *data, mlx_image_t *img)
{
	int	x;
	int	y;
	int	p_size;
	int	centered;

	p_size = 16;
	centered = p_size / 2;
	x = (int)data->file_data.player->x;
	while (x - p_size < data->file_data.player->x)
	{
		y = (int)data->file_data.player->y;
		while (y - p_size < data->file_data.player->y)
		{
			// fprintf(stderr, "%d | %d\n", x - centered, y - centered); // ? testing
			// log_val(data, "draw_player", 'P'); // ? testing
			if (!check_put_pixel(data, x - centered, y - centered))
				return (false);
			// log_val(data, "draw_player", 'G'); // ? testing
			// log_val(data, "draw_player", 'D'); // ? testing
			// log_val(data, "draw_player", 'A'); // ? testing
			// fprintf(stderr, "%d | %d\n", x - p_size, y - p_size); // ? testing
			mlx_put_pixel(img, x - centered, y - centered, YELLOW); 
			y++;
		}
		x++;
	}
	if (!dda_draw_direction(data, data->graphics->img))
		return (false);
	return (true);
}
