
#include <parser.h>

bool	check_map(const char *file_name, t_file_data *file_data)
{
	file_data->fd = open(file_name, O_RDONLY);
	// file_data->fd = -1; // ? testing
	if (file_data->fd == ERROR)
		return (error_msg("Opening scene file"));
	file_data->line = read_scene_file(file_data);
	// file_data->line = NULL; // ? testing
	if (!file_data->line)
		return (error_msg("Reading scene file"));
	if (!read_scene_data(file_data))
		return (error_msg("Parsing scene file data"));
	if (!check_identifiers(&file_data->identifiers, ".png"))
		return (error_msg("Invalid identifiers"));
	if (!check_map_content((const char **)file_data->map_data.map))
		return (error_msg("Invalid content in map"));
	// print_map(file_data->map_content); // ? testing
	if (!check_walls(file_data))
		return (error_msg("Surrounding walls required"));
	file_data->map_data.col = get_max_line_len((const char **)file_data->map_data.map);
	if (file_data->map_data.col == ERROR)
		return (error_msg("Getting max line len"));
	// print_map(file_data->map_data.map); // ? testing
	// printf("%lld\n", file_data->map_data.row);
	// system("leaks cub3D"); // ? testing
	return (true);
}
