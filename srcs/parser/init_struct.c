#include <parser.h>

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
	file_data->player = player;
	return (true);
}

static t_rgb	*st_init_colors_data(void)
{
	t_rgb	*rgb_data;

	rgb_data = (t_rgb *)malloc(sizeof(t_rgb));
	if (!rgb_data)
		return (NULL);
	rgb_data->red = NA;
	rgb_data->green = NA;
	rgb_data->blue = NA;
	return (rgb_data);
}

static bool	st_init_identifiers_data(t_file_data *file_data)
{
	t_identifiers_data	*identifiers_data;

	identifiers_data = (t_identifiers_data *)malloc(sizeof(t_identifiers_data));
	if (!identifiers_data)
		return (false);
	identifiers_data->ceiling = st_init_colors_data();
	identifiers_data->floor = st_init_colors_data();
	if (!identifiers_data->ceiling || !identifiers_data->floor)
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
	t_file_data *file_data;

	file_data = (t_file_data *)malloc(sizeof(t_file_data));
	if (!file_data)
		return (error_msg("Malloc file_data struct"));
	file_data->buflen = NA;
	file_data->fd = NA;
	file_data->file_extension = ".cub";
	file_data->line = NULL;
	file_data->scene = NULL;
	if (!st_init_map_data(file_data))
		return (error_msg("Initializing map data struct"));
	if (!st_init_identifiers_data(file_data))
		return (error_msg("Initializing identifiers data struct"));
	if (!st_init_player_data(file_data))
		return (error_msg("Initializing player data struct"));
	data->file_data = file_data;
	return (true);
}
