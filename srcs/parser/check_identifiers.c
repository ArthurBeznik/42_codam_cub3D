#include <parser.h>

bool	check_identifiers(t_identifiers_data *id_data, \
	const char *extension)
{
	if (!id_data)
		return (error_msg("Fetching identifier data"));
	if (!id_data->path_to_north_texture || !id_data->path_to_south_texture || \
		!id_data->path_to_east_texture || !id_data->path_to_west_texture)
		return (error_msg("Fetching path of textures"));
	if (!check_ext(id_data->path_to_north_texture, extension) || \
		!check_ext(id_data->path_to_south_texture, extension) || \
		!check_ext(id_data->path_to_east_texture, extension) || \
		!check_ext(id_data->path_to_west_texture, extension))
		return (error_msg("Wrong extension (.png required)"));
	return (true);
}

bool	check_identifiers_values(char **tmp, t_file_data *data)
{
	if ((tmp[0][0] == 'N' || tmp[0][0] == 'S' || \
		tmp[0][0] == 'W' || tmp[0][0] == 'E') && !tmp[1])
	{
		data->only_texture_id = true;
		return (false);
	}
	return (true);
}
