#include <parser.h>

static bool	mark_found_colors(t_file_data *data, const char *line, \
	bool is_valid)
{
	if (line[0] == 'F' && is_valid && !data->floor_found)
		data->floor_found = true;
	else if (line[0] == 'C' && is_valid && !data->ceiling_found)
		data->ceiling_found = true;
	else if (line[0] == 'C' && data->ceiling_found == true)
		return (error_msg("Duplicate color identifier"));
	else if (line[0] == 'F' && data->floor_found == true)
		return (error_msg("Duplicate color identifier"));
	else
		is_valid = false;
	return (is_valid);
}

static void	save_ceiling(t_file_data *data, const int r, const int g, \
	const int b)
{
	data->identifiers.ceiling.r = r;
	data->identifiers.ceiling.g = g;
	data->identifiers.ceiling.b = b;
	data->identifiers.ceiling.a = 255;
}

static void	save_floor(t_file_data *data, const int r, const int g, const int b)
{
	data->identifiers.floor.r = r;
	data->identifiers.floor.g = g;
	data->identifiers.floor.b = b;
	data->identifiers.floor.a = 255;
}

static bool	save_values(t_file_data *data, const char **rgb_values, \
	const char c)
{
	int		r;
	int		g;
	int		b;

	data->red = ft_strtrim(rgb_values[0], " ");
	data->green = ft_strtrim(rgb_values[1], " ");
	data->blue = ft_strtrim(rgb_values[2], " ");
	if (!check_rgb_values(rgb_values))
	{
		free_colors_helpers(data->red, data->green, data->blue);
		return (false);
	}
	r = ft_atoi(data->red);
	g = ft_atoi(data->green);
	b = ft_atoi(data->blue);
	free_colors_helpers(data->red, data->green, data->blue);
	if (rgb_values[3])
		return (error_msg("Invalid color value"));
	if (c == 'F')
		save_floor(data, r, g, b);
	else if (c == 'C')
		save_ceiling(data, r, g, b);
	return (check_color_range(r, g, b));
}

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
		is_valid = mark_found_colors(data, line, is_valid);
		free(line_without_id);
		free_2d(rgb_values);
	}
	return (is_valid);
}
