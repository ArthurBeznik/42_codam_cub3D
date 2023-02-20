
#include <parser.h>

static bool	st_check_color_range(int color)
{
	// color = 270; // ? testing
	// color = -67; // ? testing
	// color = 9999999; // ? testing
	if (color >= 0 && color <= 255)
		return (true);
	return (false);
}

static bool	st_check_colors(t_rgb *colors)
{
	// colors = NULL; // ? testing
	if (!colors)
		return (false);
	if (!st_check_color_range(colors->red)
		|| !st_check_color_range(colors->green)
		|| !st_check_color_range(colors->blue))
		return (false);
	return (true);
}

bool	check_identifiers(t_identifiers_data *id_data, \
	char *extension)
{
	if (!id_data)
		return (false);
	if (!id_data->path_to_north_texture || !id_data->path_to_south_texture \
		|| !id_data->path_to_east_texture || !id_data->path_to_west_texture \
		|| !id_data->floor || !id_data->ceiling)
		return (false);
	if (!check_ext(id_data->path_to_north_texture, extension)
		|| !check_ext(id_data->path_to_south_texture, extension)
		|| !check_ext(id_data->path_to_east_texture, extension)
		|| !check_ext(id_data->path_to_west_texture, extension))
		return (false);
	if (!st_check_colors(id_data->floor)
		|| !st_check_colors(id_data->ceiling))
		return (false);
	return (true);
}
