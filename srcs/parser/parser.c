
#include <parser.h>

void	init_map_file_data(t_file_data *file_data)
{
	t_identifiers_data	*identifiers_data;
	t_rgb				*floor;
	t_rgb				*ceiling;

	identifiers_data = (t_identifiers_data *)malloc(sizeof(t_identifiers_data));
	floor = (t_rgb *)malloc(sizeof(t_rgb));
	ceiling = (t_rgb *)malloc(sizeof(t_rgb));
	file_data->identifiers = identifiers_data;
	file_data->identifiers->floor = floor;
	file_data->identifiers->ceiling = ceiling;
	file_data->map_extension = ".cub";
	file_data->buflen = 999;
	file_data->fd = 999;
	file_data->identifiers->path_to_north_texture = NULL;
	file_data->identifiers->path_to_south_texture = NULL;
	file_data->identifiers->path_to_west_texture = NULL;
	file_data->identifiers->path_to_east_texture = NULL;
	file_data->identifiers->ceiling->red = 999;
	file_data->identifiers->ceiling->green = 999;
	file_data->identifiers->ceiling->blue = 999;
	file_data->identifiers->floor->red = 999;
	file_data->identifiers->floor->green = 999;
	file_data->identifiers->floor->blue = 999;
}

bool	parser(int argc, char *argv[], t_file_data *file_data)
{
	init_map_file_data(file_data);
	if (argc != 2)
		return (error_msg("Usage: ./cub3D <file_name>.cub"));
	if (!check_ext(argv[1], file_data->map_extension))
		return (false);
	if (!check_map(argv[1], file_data))
		return (false);
	return (true);
}
