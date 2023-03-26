#include <graphics.h>
/**
 * x1:
 * 	. i * cos(angle)	=> pixel * angle based on x
 * 	. + player dx 		=> (given the direction) value to be added to x
*/
bool draw_direction(t_general_data *data, mlx_image_t *img, double angle)
{
	int		i;
	int		d_size;
	double	x1;
    double	y1;

	d_size = 16;
	i = 0;
	while (i < d_size)
	{
		// log_positions(data, "draw_dir", 'A');
		x1 = (i * cos((angle))) + data->file_data->player->x;
        y1 = (i * sin((angle))) + data->file_data->player->y;
		// fprintf(stderr, "x1 | y1: %f | %f\n", x1, y1); // ? testing
		// log_positions(data, "draw_dir", 'D'); // ? testing
		// log_positions(data, "draw_dir", 'P'); // ? testing
		if (!check_put_pixel(data, x1, y1))
			return (false);	
		mlx_put_pixel(img, x1, y1, 0xFF000090);
		i++;
	}
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
	x = (int)data->file_data->player->x;
	while (x - p_size < data->file_data->player->x)
	{
		y = (int)data->file_data->player->y;
		while (y - p_size < data->file_data->player->y)
		{
			if (!check_put_pixel(data, x - centered, y - centered))
			// if (!check_put_pixel(data, -100, y - size / 2)) // ? testing
            	return (false);
			// log_positions(data, "draw_player", 'P'); // ? testing
			// log_positions(data, "draw_player", 'G'); // ? testing
			// log_positions(data, "draw_player", 'D'); // ? testing
			// log_positions(data, "draw_player", 'A'); // ? testing
			// fprintf(stderr, "%d | %d\n", x - centered, y - centered); // ? testing
			// fprintf(stderr, "%d | %d\n", x - p_size, y - p_size); // ? testing
			mlx_put_pixel(img, x - centered, y - centered, 0xFFFF00FF);
			y++;
		}
		x++;
	}
	if (!draw_direction(data, data->graphics->img, data->file_data->player->angle))
		return (false);
	return (true);
}