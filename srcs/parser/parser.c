
#include <parser.h>

void	init_map_file_data(t_file_data *file_data)
{
	t_identifiers_data	*id_data = (t_identifiers_data *)malloc(sizeof(t_identifiers_data));
	t_rgb				*rgb_f = (t_rgb *)malloc(sizeof(t_rgb));
	t_rgb				*rgb_c = (t_rgb *)malloc(sizeof(t_rgb));

	file_data->map_extension = ".cub";
	file_data->buflen = 1;
	file_data->fd = 0;
	id_data->path_to_north_texture = "./textures/empty.png";
	id_data->path_to_south_texture = "./textures/empty.png";
	id_data->path_to_west_texture = "./textures/empty.png";
	id_data->path_to_east_texture = "./textures/empty.png";
	rgb_f->red = 220;
	rgb_f->green = 100;
	rgb_f->blue = 0;
	rgb_c->red = 225;
	rgb_c->green = 30;
	rgb_c->blue = 0;
	id_data->floor = rgb_f;
	id_data->ceiling = rgb_c;
	file_data->identifiers = id_data;
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
