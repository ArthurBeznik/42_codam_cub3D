
#include <parser.h>

size_t	ft_count_rows(char **scene)
{
	size_t i;

	i = 0;
	while (scene[i])
		i++;
	return (i);
}

void	free_2d(char **array)
{
	while (*array)
	{
		free(*array);
		array++;
	}
	return ;
}

void	find_identifier(char *line, t_file_data *data)
{
	if (line[0] == 'N')
		data->identifiers->path_to_north_texture = ft_strdup(line);
	else if (line[0] == 'S')
		data->identifiers->path_to_south_texture = ft_strdup(line);
	else if (line[0] == 'W')
		data->identifiers->path_to_west_texture = ft_strdup(line);
	else if (line[0] == 'E')
		data->identifiers->path_to_east_texture = ft_strdup(line);
}

void	save_values(t_file_data *data, char **rgb_values, int id)
{
	if (id == 0)
	{
		data->identifiers->floor->red = ft_atoi(rgb_values[0]);
		data->identifiers->floor->green = ft_atoi(rgb_values[1]);
		data->identifiers->floor->blue = ft_atoi(rgb_values[2]);
		if (data->identifiers->floor->red == ERROR
			|| data->identifiers->floor->green == ERROR
			|| data->identifiers->floor->blue == ERROR)
			{
				free_2d(rgb_values);
				return ;
			}
	}
	else if (id == 1)
	{
		data->identifiers->ceiling->red = ft_atoi(rgb_values[0]);
		data->identifiers->ceiling->green = ft_atoi(rgb_values[1]);
		data->identifiers->ceiling->blue = ft_atoi(rgb_values[2]);
		if (data->identifiers->ceiling->red == ERROR
			|| data->identifiers->ceiling->green == ERROR
			|| data->identifiers->ceiling->blue == ERROR)
		{
			free_2d(rgb_values);
			return ;
		}
	}
}

void	find_colors(char *line, t_file_data *data)
{
	char *line_without_id;
	char **rgb_values;

	if ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
	{
		line_without_id = ft_substr(line, 2, ft_strlen(line - 2));
		if (!line_without_id)
			return ;
		rgb_values = ft_split(line_without_id, ',');
		if (!rgb_values)
		{
			free(line_without_id);
			return ;
		}
		if (line[0] == 'F')
			save_values(data, rgb_values, 0);
		else if (line[0] == 'C')
			save_values(data, rgb_values, 1);
		free(line_without_id);
		free_2d(rgb_values);
	}
}

bool	check_scene_file_order(t_file_data *data)
{
	int i;

	// return (false); // ? testing failure
	i = 0;
	while (i < 6)
	{
		if (data->scene[i][0] == '1')
			return (error_msg("Scene file starts with map content"));
		i++;
	}
	if (data->scene[data->rows_count - 1][0] != '1')
		return (error_msg("Scene file does not end with map content"));
	return (true);
}
