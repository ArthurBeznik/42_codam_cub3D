#include <parser.h>
#include <cub3D.h>

bool	parser(int argc, char *argv[], t_general_data *data)
{
	if (argc != 2)
		return (error_msg("Usage: ./cub3D <file_name>.cub"));
	init_file_data(data);
	if (!check_ext(argv[1], data->file_data.file_extension))
		return (false);
	if (!check_map(argv[1], &data->file_data))
		return (false);
	return (true);
}
