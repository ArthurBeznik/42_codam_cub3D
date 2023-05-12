#include <cub3D.h>

static unsigned int	reverse_bits(unsigned int num)
{
	unsigned int	nb_bits;
	unsigned int	rev_num;
	unsigned int	i;

	nb_bits = sizeof(num) * 8;
	rev_num = 0;
	i = 0;
	while (i < nb_bits)
	{
		if ((num & (1 << i)))
			rev_num |= 1 << ((nb_bits - 1) - i);
		i++;
	}
	return (rev_num);
}

static void	put_multi_pixels(mlx_image_t *img, unsigned int color, \
	int pixels, int offset)
{
	uint32_t	*px;
	int			i;

	px = (uint32_t *)img->pixels;
	i = 0;
	while (i < pixels)
	{
		px[offset + i] = color;
		i++;
	}
}

void	draw_ceiling_floor(t_general_data *data)
{
	put_multi_pixels(data->graphics.img_3d, \
		reverse_bits(data->file_data.identifiers.ceiling.rgba), \
		((data->graphics.height / 3 * 2) * data->graphics.width), 0);
	put_multi_pixels(data->graphics.img_3d, \
		reverse_bits(data->file_data.identifiers.floor.rgba), \
		(data->graphics.height / 3 * data->graphics.width), \
		((data->graphics.height / 3 * 2) * data->graphics.width));
}
