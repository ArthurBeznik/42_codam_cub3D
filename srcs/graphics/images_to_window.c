#include "cub3D.h"

// static bool	print_wall(t_general_data *data, size_t i, ssize_t x, ssize_t y)
// {
// 	if (data->file_data->map_data->map[i] == '1')
// 	{
// 		if (x == 0 || y == 0 || y == data->file_data->map_data->rows_count \
// 							|| x == data->file_data->map_data->max_line_len - 1)
// 		{
// 			if (mlx_image_to_window(data->mlx, data->img[WALL], \
// 												x * PIXELS, y * PIXELS) == -1)
// 				return (free_array(data->img, "image_to_window failed", \
// 															data), false);
// 		}
// 		else
// 		{
// 			if (mlx_image_to_window(data->mlx, data->img[TILE], \
// 												x * PIXELS, y * PIXELS) == -1)
// 				return (free_array(data->img, "image_to_window failed", \
// 															data), false);
// 		}
// 	}
// 	return (true);
// }

static bool	images_to_window2(t_graphics *graphics, size_t x, size_t y, \
													int32_t macro)
{
	// if (macro >= PICKUP && macro <= MAP_EXIT)
	// {
    if (mlx_image_to_window(graphics->mlx, graphics->images[macro], \
												x * PIXELS, y * PIXELS) == -1)
		{
        	error_msg("image_to_window failed");
            terminate(graphics);

        }
	// }
	return (true);
}


bool	images_to_window(t_general_data *data, t_graphics *graphics, size_t i)
{
	size_t	x;
	size_t	y;
    size_t  j;
	int32_t	macro;

	while (data->file_data->map_data->map[i])
	{
		x = i % (data->file_data->map_data->max_line_len + 1);
		y = i / (data->file_data->map_data->max_line_len + 1);
        j = 0;
        while (j < (size_t)data->file_data->map_data->max_line_len)
        {
            if (data->file_data->map_data->map[i][j] == '1')
            {
                if (data->file_data->map_data->map[i][j] == '1')
                {
                    if (x == 0 || y == 0 || y == (size_t)data->file_data->map_data->rows_count \
                                || x == (size_t)data->file_data->map_data->max_line_len - 1)
                    {
                        if (mlx_image_to_window(graphics->mlx, graphics->images[WALL], \
                                                    x * PIXELS, y * PIXELS) == -1)
                        {
                            error_msg("image_to_window failed");
                            terminate(graphics);
                        }
                    }
                }
                // if (!(print_wall(data, i, x, y)))
                // 	return (false);
            }
            else if (data->file_data->map_data->map[i][j] == 'N' || \
                    data->file_data->map_data->map[i][j] == 'S' || \
                    data->file_data->map_data->map[i][j] == 'E' || \
                    data->file_data->map_data->map[i][j] == 'W')
                macro = PLAYER;
            j++;
        }
		if (!(images_to_window2(graphics, x, y, macro)))
			return (false);
		i++;
	}
	return (true);
}
