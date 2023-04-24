#include <parser.h>
#include <cub3D.h>

static bool	st_init_player_data(t_file_data *file_data)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (false);
	player->facing = 'X';
	player->x = NA;
	player->y = NA;
	player->angle = NA;
	player->dir_x = NA;
	player->dir_y = NA;
	file_data->player = player;
	return (true);
}

static bool	st_init_identifiers_data(t_file_data *file_data)
{
	t_identifiers_data	*identifiers_data;

	identifiers_data = (t_identifiers_data *)malloc(sizeof(t_identifiers_data));
	if (!identifiers_data)
		return (false);
	identifiers_data->path_to_north_texture = NULL;
	identifiers_data->path_to_south_texture = NULL;
	identifiers_data->path_to_west_texture = NULL;
	identifiers_data->path_to_east_texture = NULL;
	file_data->identifiers = identifiers_data;
	return (true);
}

static bool	st_init_map_data(t_file_data *file_data)
{
	t_map_data	*map_data;

	map_data = (t_map_data *)malloc(sizeof(t_map_data));
	if (!map_data)
		return (false);
	map_data->copy = NULL;
	map_data->map = NULL;
	map_data->row = NA;
	map_data->col = NA;
	file_data->map_data = map_data;
	return (true);
}

bool	init_file_data(t_general_data *data)
{
	// t_file_data file_data;

	// file_data = (t_file_data *)malloc(sizeof(t_file_data));
	// if (!file_data)
	// 	return (error_msg("Malloc file_data struct"));
	data->file_data.buflen = NA;
	data->file_data.fd = NA;
	data->file_data.file_extension = ".cub";
	data->file_data.line = NULL;
	data->file_data.scene = NULL;
	data->file_data.ceiling_found = false;
	data->file_data.floor_found = false;
	data->file_data.duplicate_identifier = false;
	data->file_data.duplicate_color = false;
	if (!st_init_map_data(&data->file_data))
		return (error_msg("Initializing map data struct"));
	if (!st_init_identifiers_data(&data->file_data))
		return (error_msg("Initializing identifiers data struct"));
	if (!st_init_player_data(&data->file_data))
		return (error_msg("Initializing player data struct"));
	return (true);
}
