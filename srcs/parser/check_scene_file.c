
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
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i] != NULL)
			free(array[i]);
		i++;
	}
	free(array);
	return ;
}

void	find_identifier(char *line, t_file_data *data)
{
	char **tmp;

	tmp = ft_split(line, ' ');
	// tmp = NULL; // ? testing
	if (!tmp)
		return ;
	if (ft_strlen(tmp[0]) > 2)
	// int x = 4; // ? testing
	// if (x > 2) // ? testing
	{
		free_2d(tmp);
		return ;
	}
	if (tmp[0][0] == 'N' || !ft_strncmp("NO", tmp[0], 2))
		data->identifiers->path_to_north_texture = ft_strdup(tmp[1]);
		// data->identifiers->path_to_north_texture = NULL; // ? testing
	else if (tmp[0][0] == 'S' || !ft_strncmp("SO", tmp[0], 2))
		data->identifiers->path_to_south_texture = ft_strdup(tmp[1]);
	else if (tmp[0][0] == 'W' || !ft_strncmp("WE", tmp[0], 2))
		data->identifiers->path_to_west_texture = ft_strdup(tmp[1]);
	else if (tmp[0][0] == 'E' || !ft_strncmp("EA", tmp[0], 2))
		data->identifiers->path_to_east_texture = ft_strdup(tmp[1]);
	free_2d(tmp);
}

void	save_values(t_file_data *data, char **rgb_values, char c)
{
	if (c == 'F')
	{
		data->identifiers->floor->red = ft_atoi(rgb_values[0]);
		// data->identifiers->floor->red = ft_atoi("999999999999999"); // ? testing
		data->identifiers->floor->green = ft_atoi(rgb_values[1]);
		// data->identifiers->floor->green = -1; // ? testing
		data->identifiers->floor->blue = ft_atoi(rgb_values[2]);
		// data->identifiers->floor->blue = ft_atoi("-1"); // ? testing
	}
	else if (c == 'C')
	{
		data->identifiers->ceiling->red = ft_atoi(rgb_values[0]);
		// data->identifiers->ceiling->red = ft_atoi("18446744073709551615"); // ? testing
		data->identifiers->ceiling->green = ft_atoi(rgb_values[1]);
		data->identifiers->ceiling->blue = ft_atoi(rgb_values[2]);
	}
}

void	find_colors(char *line, t_file_data *data)
{
	char *line_without_id;
	char **rgb_values;

	if ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
	{
		line_without_id = ft_substr(line, 1, ft_strlen(line));
		// line_without_id = NULL; // ? testing
		if (!line_without_id)
			return ;
		rgb_values = ft_split(line_without_id, ',');
		// rgb_values = NULL; // ? testing
		if (!rgb_values)
		{
			free(line_without_id);
			return ;
		}
		save_values(data, rgb_values, line[0]);
		free(line_without_id);
		free_2d(rgb_values);
	}
}

bool	check_scene_file_order(t_file_data *data)
{
	int i;

	// return (false); // ? testing
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
