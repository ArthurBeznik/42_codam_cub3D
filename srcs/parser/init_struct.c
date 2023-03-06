#include <parser.h>

bool	init_player_data(t_player *player)
{
	// t_player	*player;

	// player = (t_player *)malloc(sizeof(t_player));
	// if (!player)
	// 	return (false);
	player->facing = 'X';
	player->x = 999;
	player->y = 999;
	// file_data->player = player;
	return (true);
}

t_rgb	*init_colors_data(t_rgb *rgb_data)
// void	init_colors_data(t_rgb *rgb_data)
{
	// t_rgb	*rgb_data;
	// t_rgb	rgb_data;

	// rgb_data = (t_rgb *)malloc(sizeof(t_rgb));
	// if (!rgb_data)
	// 	return (NULL);
	rgb_data->red = 999;
	rgb_data->green = 999;
	rgb_data->blue = 999;
	return (rgb_data);
}

bool	init_identifiers_data(t_identifiers_data *identifiers_data)
{
	t_rgb	ceiling_data;
	t_rgb	floor_data;
	// t_identifiers_data	identifiers_data;

	// file_data->identifiers = &identifiers_data;
	// identifiers_data = (t_identifiers_data *)malloc(sizeof(t_identifiers_data));
	// if (!identifiers_data)
	// 	return (false);
	identifiers_data->ceiling = &ceiling_data;
	identifiers_data->floor = &floor_data;
	identifiers_data->ceiling = init_colors_data(&ceiling_data);
	// init_colors_data(identifiers_data->ceiling);
	identifiers_data->floor = init_colors_data(&floor_data);
	// init_colors_data(identifiers_data->floor);
	// if (!file_data->identifiers->ceiling || !file_data->identifiers->floor)
	// 	return (false);
	identifiers_data->path_to_north_texture = NULL;
	identifiers_data->path_to_south_texture = NULL;
	identifiers_data->path_to_west_texture = NULL;
	identifiers_data->path_to_east_texture = NULL;
	// file_data->identifiers = identifiers_data;
	return (true);
}

bool	init_map_data(t_map_data *map_data)
{
	// t_map_data	*map_data;
	// t_map_data	map_data;

	// file_data->map_data = &map_data;
	// map_data = (t_map_data *)malloc(sizeof(t_map_data));
	// if (!map_data)
	// 	return (false);
	map_data->copy = NULL;
	map_data->map = NULL;
	map_data->rows_count = 999;
	map_data->max_line_len = 999;
	// file_data->map_data = map_data;
	return (true);
}

bool	init_file_data(t_file_data *file_data)
{
	// t_file_data *file_data;
	t_map_data			map_data;
	t_identifiers_data	identifiers_data;
	t_player			player;

	file_data->map_data = &map_data;
	file_data->identifiers = &identifiers_data;
	file_data->player = &player;
	// file_data = (t_file_data *)malloc(sizeof(t_file_data));
	// if (!file_data)
	// 	return (error_msg("Malloc file_data struct"));
	file_data->buflen = 999;
	file_data->fd = 999;
	file_data->file_extension = ".cub";
	file_data->line = NULL;
	file_data->scene = NULL;
	if (!init_map_data(file_data->map_data))
		return (error_msg("Initializing map data struct"));
	if (!init_identifiers_data(file_data->identifiers))
		return (error_msg("Initializing identifiers data struct"));
	if (!init_player_data(file_data->player))
		return (error_msg("Initializing player data struct"));
	// data->file_data = data->file_data;
	return (true);
}
