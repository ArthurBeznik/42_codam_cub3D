#include <parser.h>

static char	**create_map(t_file_data *data, const int nb_rows)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	j = 0;
	map = (char **)malloc(sizeof(char *) * (nb_rows - 5));
	if (!map)
		return (NULL);
	while (i < nb_rows)
	{
		if (i >= 6)
		{
			map[j] = ft_strdup(data->scene[i]);
			if (!map[j])
			{
				free_2d(map);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	map[j] = NULL;
	return (map);
}

static bool	valid_identifiers(t_file_data *data)
{
	if (data->duplicate_identifier == true)
		return (error_msg("Duplicate texture identifier"));
	if (data->only_texture_id == true)
		return (error_msg("Missing textures"));
	if (data->ceiling_found == false || data->floor_found == false)
		return (error_msg("Missing ceiling or floor identifier"));
	return (true);
}

static bool	find_identifiers(t_file_data *data, const int nb_rows)
{
	int	i;

	i = 0;
	while (i < nb_rows)
	{
		if ((data->identifiers.ceiling.rgba != 0 || \
			data->identifiers.floor.rgba != 0) && \
			(!data->identifiers.path_to_east_texture || \
			!data->identifiers.path_to_north_texture || \
			!data->identifiers.path_to_south_texture || \
			!data->identifiers.path_to_west_texture))
			return (error_msg("Colors are defined but not textures"));
		find_textures(data->scene[i], data);
		if (find_colors(data->scene[i], data) == false)
			return (false);
		i++;
	}
	if (!valid_identifiers(data))
		return (false);
	if (!check_scene_file_order(data))
		return (error_msg("Invalid scene file order"));
	return (true);
}

bool	read_scene_data(t_file_data *data)
{
	int	nb_rows;

	data->scene = ft_split(((const char *)data->line), '\n');
	if (!data->scene)
		return (error_msg("Split to scene"));
	nb_rows = ft_count_rows((const char **)data->scene);
	if (nb_rows == ERROR)
		return (error_msg("Counting rows of scene file"));
	if (!find_identifiers(data, nb_rows))
		return (false);
	data->map_data.map = create_map(data, nb_rows);
	if (!data->map_data.map)
		return (error_msg("Invalid map"));
	if (data->scene != NULL)
	{
		free_2d(data->scene);
		data->scene = NULL;
	}
	return (true);
}
