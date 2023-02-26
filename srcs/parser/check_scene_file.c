
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

/**
 * as of now, identifiers has never been init / allocated => this will fail
*/
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

/**
 * same for here
*/
void	find_floor_colors(char *line, t_file_data *data)
{
	char **spliting_F;
	char **spliting_comma;

	if (line[0] == 'F' && line[1] == ' ')
	{
		spliting_F = ft_split(line, 'F');
		if (!spliting_F)
			return ;
		spliting_comma = ft_split(spliting_F[0], ',');
		if (!spliting_comma)
			return ;
		data->identifiers->floor->red = ft_atoi(spliting_comma[0]);
		data->identifiers->floor->green = ft_atoi(spliting_comma[1]);
		data->identifiers->floor->blue = ft_atoi(spliting_comma[2]);
		if (data->identifiers->floor->red == ERROR || data->identifiers->floor->green == ERROR \
			|| data->identifiers->floor->blue == ERROR)
		{
			free_2d(spliting_F);
			return ;
		}
		free_2d(spliting_F);
	}
}

void	find_ceiling_colors(char *line, t_file_data *data)
{
	char **spliting_C;
	char **spliting_commda;

	if (line[0] == 'C' && line[1] == ' ')
	{
		spliting_C = ft_split(line, 'C');
		if (!spliting_C)
			return ;
		spliting_commda = ft_split(spliting_C[0], ',');
		if (!spliting_commda)
			return ;
		data->identifiers->ceiling->red = ft_atoi(spliting_commda[0]);
		data->identifiers->ceiling->green = ft_atoi(spliting_commda[1]);
		data->identifiers->ceiling->blue = ft_atoi(spliting_commda[2]);
		if (data->identifiers->ceiling->red == ERROR || data->identifiers->ceiling->green == ERROR \
			|| data->identifiers->ceiling->blue == ERROR)
		{
			free_2d(spliting_C);
			return ;
		}
		free_2d(spliting_C);
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
