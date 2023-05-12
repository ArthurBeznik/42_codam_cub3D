#include <parser.h>
#include <cub3D.h>

static void	init_player_data(t_file_data *file_data)
{
	file_data->player.facing = 'X';
	file_data->player.x = NA;
	file_data->player.y = NA;
	file_data->player.angle = NA;
}

static void	init_identifiers_data(t_file_data *file_data)
{
	file_data->identifiers.path_to_north_texture = NULL;
	file_data->identifiers.path_to_south_texture = NULL;
	file_data->identifiers.path_to_west_texture = NULL;
	file_data->identifiers.path_to_east_texture = NULL;
}

static void	init_map_data(t_file_data *file_data)
{
	file_data->map_data.copy = NULL;
	file_data->map_data.map = NULL;
	file_data->map_data.row = NA;
	file_data->map_data.col = NA;
}

void	init_file_data(t_general_data *data)
{
	data->file_data.buflen = NA;
	data->file_data.fd = NA;
	data->file_data.file_extension = ".cub";
	data->file_data.line = NULL;
	data->file_data.scene = NULL;
	data->file_data.ceiling_found = false;
	data->file_data.floor_found = false;
	data->file_data.duplicate_identifier = false;
	data->file_data.duplicate_color = false;
	data->file_data.only_texture_id = false;
	init_map_data(&data->file_data);
	init_identifiers_data(&data->file_data);
	init_player_data(&data->file_data);
}
