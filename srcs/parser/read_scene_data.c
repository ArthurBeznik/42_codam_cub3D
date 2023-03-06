#include <parser.h>

/**
 * ? <25 lines without testing comments
*/
char	**create_map(t_file_data *data, int nb_rows)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	j = 0;
	map = (char **)malloc(sizeof(char *) * (nb_rows - 5));
	// map = NULL; // ? testing
	if (!map)
		return (NULL);
	while (i < nb_rows)
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

bool	find_identifiers_data(t_file_data *data, int nb_rows)
{
	int	i;

	i = 0;
	while (i < nb_rows)
	{
		find_textures(data->scene[i], data);
		find_colors(data->scene[i], data);
		i++;
	}
	if (!check_scene_file_order(data, nb_rows))
	{
		free_2d(data->scene);
		return (error_msg("Invalid scene file order"));
	}
	return (true);
}

bool	read_scene_data(t_file_data *data)
{
	int	nb_rows;

	data->scene = ft_split(((const char *)data->line), '\n');
	if (!data->scene)
		return (error_msg("Split to scene"));
	nb_rows = ft_count_rows((const char **)data->scene);
	// nb_rows == -1; // ? testing
	if (nb_rows == ERROR)
	{
		free_2d(data->scene);
		return (error_msg("Counting rows of scene file"));
	}
	if (!find_identifiers_data(data, nb_rows))
		return (false);
	// data->map_content = create_map(data);
	data->map_data->map = create_map(data, nb_rows);
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
