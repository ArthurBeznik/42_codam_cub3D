
#include <parser.h>

char	**create_map(t_file_data *data)
{
	size_t	i;
	size_t	j;
	char	**map;

	i = 0;
	j = 0;
	map = (char **)malloc(sizeof(char *) * (data->map_data->rows_count - 5));
	// map = NULL; // ? testing
	if (!map)
		return (NULL);
	while (i < data->map_data->rows_count)
	{
		if (i >= 6)
		{
			map[j] = ft_strdup(data->scene[i]);
			// map[j] = NULL; // ? testing
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

/**
 * TODO fix too many lines
*/
bool	read_scene_data(t_file_data *data)
{
	size_t i;

	i = 0;
	data->scene = ft_split(((const char *)data->line), '\n');
	// data->scene = NULL; // ? testing
	if (!data->scene)
		return (error_msg("Split to scene"));
	data->map_data->rows_count = ft_count_rows(data->scene);
	// data->rows_count = NULL; // ? testing
	if (!data->map_data->rows_count)
	{
		free_2d(data->scene);
		return (error_msg("Count rows"));
	}
	while (i < data->map_data->rows_count)
	{
		find_identifier(data->scene[i], data);
		find_colors(data->scene[i], data);
		i++;
	}
	if (!check_scene_file_order(data))
	{
		free_2d(data->scene);
		return (error_msg("Invalid scene file order"));
	}
	// data->map_content = create_map(data);
	data->map_data->map = create_map(data);
	// data->map_content = NULL; // ? testing
	if (!data->map_data->map)
	{
		free_2d(data->scene);
		return (error_msg("Invalid map"));
	}
	free_2d(data->scene);
	// system("leaks cub3D"); // ? testing
	return (true);
}