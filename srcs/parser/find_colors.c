#include <parser.h>

/**
 * TODO norm
*/
bool	save_values(t_file_data *data, const char **rgb_values, const char c)
{
	int	r;
	int	g;
	int	b;

	if (!check_rgb_values(rgb_values))
		return (false);
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
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
	return (check_color_range(r, g, b));
}
/**
 * TODO norm
*/
bool	find_colors(const char *line, t_file_data *data)
{
	char	*line_without_id;
	char	**rgb_values;
	bool	is_valid;

	is_valid = true;
	if ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
	{
		line_without_id = ft_substr(line, 1, ft_strlen(line));
		if (!line_without_id)
			return (false);
		rgb_values = ft_split(line_without_id, ',');
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
