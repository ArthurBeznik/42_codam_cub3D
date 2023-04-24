#include <parser.h>

void	find_textures(const char *line, t_file_data *data)
{
	char	**tmp;

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
	{
		if (data->identifiers.path_to_north_texture)
		{
			free(data->identifiers.path_to_north_texture);
			data->duplicate_identifier = true;
		}
		data->identifiers.path_to_north_texture = ft_strdup(tmp[1]);
	}
		// data->identifiers.path_to_north_texture = NULL; // ? testing
	else if (tmp[0][0] == 'S' || !ft_strncmp("SO", tmp[0], 2))
	{
		if (data->identifiers.path_to_south_texture)
		{
			free(data->identifiers.path_to_south_texture);
			data->duplicate_identifier = true;
		}
		data->identifiers.path_to_south_texture = ft_strdup(tmp[1]);
	}
	else if (tmp[0][0] == 'W' || !ft_strncmp("WE", tmp[0], 2))
	{
		if (data->identifiers.path_to_west_texture)
		{
			free(data->identifiers.path_to_west_texture);
			data->duplicate_identifier = true;
		}
		data->identifiers.path_to_west_texture = ft_strdup(tmp[1]);
	}
	else if (tmp[0][0] == 'E' || !ft_strncmp("EA", tmp[0], 2))
	{
		if (data->identifiers.path_to_east_texture)
		{
			free(data->identifiers.path_to_east_texture);
			data->duplicate_identifier = true;
		}
		data->identifiers.path_to_east_texture = ft_strdup(tmp[1]);
	}
	free_2d(tmp);
}

static bool	check_rgb_values(const char **rgb_values)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		j = 0;
		while (rgb_values[i][j])
		{
			if (!ft_isdigit(rgb_values[i][j]) && !(rgb_values[i][j] == ' '))
				return (error_msg("Invalid color value"));
			j++;
		}
		i++;
	}
	return (true);
}

bool	save_values(t_file_data *data, const char **rgb_values, const char c)
{
	int	r;
	int	g;
	int	b;

	if (!check_rgb_values(rgb_values))
		return (false);
	r = ft_atoi(rgb_values[0]);
	// data->identifiers.floor->red = ft_atoi("999999999999999"); // ? testing
	g = ft_atoi(rgb_values[1]);
	// data->identifiers.floor->green = -1; // ? testing
	b = ft_atoi(rgb_values[2]);
	if (rgb_values[3])
		return (error_msg("Invalid color value"));
	if (c == 'F')
	{
		data->identifiers.floor.r = r;
		data->identifiers.floor.g = g;
		data->identifiers.floor.b = b;
		data->identifiers.floor.a = 255;
	}
	else if (c == 'C')
	{
		data->identifiers.ceiling.r = r;
		data->identifiers.ceiling.g = g;
		data->identifiers.ceiling.b = b;
		data->identifiers.ceiling.a = 255;
	}
	return (st_check_color_range(r, g, b));
}

bool find_colors(const char *line, t_file_data *data)
{
	char	*line_without_id;
	char	**rgb_values;
	bool	is_valid;

	is_valid = true;
	if ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
	{
		line_without_id = ft_substr(line, 1, ft_strlen(line));
		// line_without_id = NULL; // ? testing
		if (!line_without_id)
			return (false);
		rgb_values = ft_split(line_without_id, ',');
		// rgb_values = NULL; // ? testing
		if (!rgb_values)
		{
			free(line_without_id);
			return (false);
		}
		is_valid = save_values(data, (const char **)rgb_values, line[0]);
		if (line[0] == 'F' && is_valid && !data->floor_found)
			data->floor_found = true;
		else if (line[0] == 'C' && is_valid && !data->ceiling_found)
			data->ceiling_found = true;
		else
		{
			data->duplicate_color = true;
			is_valid = false;
		}
		free(line_without_id);
		free_2d(rgb_values);
	}
	return (is_valid);
}

bool	check_scene_file_order(t_file_data *data, const int nb_rows)
{
	int	i;

	// return (false); // ? testing
	i = 0;
	while (i < 6)
	{
		if (data->scene[i][0] == '1')
			return (error_msg("Scene file starts with map content"));
		i++;
	}
	if (data->scene[nb_rows - 1][0] != '1')
		return (error_msg("Scene file does not end with map content"));
	return (true);
}
