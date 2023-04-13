#include <parser.h>


bool	parser(int argc, char *argv[], t_general_data *data)
{
	if (argc != 2)
		return (error_msg("Usage: ./cub3D <file_name>.cub"));
	if (!init_file_data(data) || !check_ext(argv[1], data->file_data->file_extension))
	{
		free_data(data, false);
		return (false);
	}
	if (!check_map(argv[1], data->file_data))
	{
		data->free_data = true;
		// system("leaks cub3D"); // ? testing
		return (false);
	}
	// system("leaks cub3D"); // ? testing
	free_2d(data->file_data->map_data->copy);
	free(data->file_data->line);
	return (true);
}
