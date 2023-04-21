#include <parser.h>

bool	st_check_color_range(const int r, const int g, const int b)
{
	// color = 270; // ? testing
	// color = -67; // ? testing
	// color = 9999999; // ? testing
	if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
		return (true);
	return (false);
}

bool	check_identifiers(t_identifiers_data *id_data, \
	const char *extension)
{
	// system("leaks cub3D"); // ? testing
	// id_data = NULL; // ? testing
	if (!id_data)
		return (error_msg("Fetching identifier data"));
	// id_data->path_to_north_texture = NULL; // ? testing
	if (!id_data->path_to_north_texture || !id_data->path_to_south_texture \
		|| !id_data->path_to_east_texture || !id_data->path_to_west_texture)
		return (error_msg("Fetching path of textures"));
	if (!check_ext(id_data->path_to_north_texture, extension)
		|| !check_ext(id_data->path_to_south_texture, extension)
		|| !check_ext(id_data->path_to_east_texture, extension)
		|| !check_ext(id_data->path_to_west_texture, extension))
		return (error_msg("Wrong extension (.png required)"));
	return (true);
}
