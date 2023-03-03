#include <parser.h>

void	init_player_data(t_file_data *file_data)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return ;
	player->facing = 'X';
	player->x = 999;
	player->y = 999;
	file_data->player = player;
}

t_rgb	*init_colors_data(t_identifiers_data *identifiers_data)
{
	t_rgb	*rgb_data;

	rgb_data = (t_rgb *)malloc(sizeof(t_rgb));
	if (!rgb_data)
		return (NULL);
	rgb_data->red = 999;
	rgb_data->green = 999;
	rgb_data->blue = 999;
	return (rgb_data);
}

void	init_identifiers_data(t_file_data *file_data)
{
	t_identifiers_data	*identifiers_data;

	identifiers_data = (t_identifiers_data *)malloc(sizeof(t_identifiers_data));
	if (!identifiers_data)
		return ;
	identifiers_data->ceiling = init_colors_data(identifiers_data);
	identifiers_data->floor = init_colors_data(identifiers_data);
	if (!identifiers_data->ceiling || !identifiers_data->floor)
		return ;
	identifiers_data->path_to_north_texture = NULL;
	identifiers_data->path_to_south_texture = NULL;
	identifiers_data->path_to_west_texture = NULL;
	identifiers_data->path_to_east_texture = NULL;
	file_data->identifiers = identifiers_data;
}

void	init_map_data(t_file_data *file_data)
{
	t_map_data	*map_data;

	map_data = (t_map_data *)malloc(sizeof(t_map_data));
	if (!map_data)
		return ;
	map_data->copy = NULL;
	map_data->map = NULL;
	map_data->rows_count = 999;
	map_data->max_line_len = 999;
	file_data->map_data = map_data;
}

void	init_file_data(t_general_data *data)
{
	t_file_data *file_data;

	file_data->buflen = 999;
	file_data->fd = 999;
	file_data->file_extension = ".cub";
	file_data->line = NULL;
	file_data->scene = NULL;
	init_map_data(file_data);
	init_identifiers_data(file_data);
	init_player_data(file_data);
	data->file_data = file_data;
}
