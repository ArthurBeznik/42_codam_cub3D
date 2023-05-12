#include <parser.h>

static void	find_east_texture(t_file_data *data, const char **tmp)
{
	if (((tmp[0][0] == 'E' && !tmp[0][1]) || \
		!ft_strncmp("EA", tmp[0], 2)) && tmp[1])
	{
		if (data->identifiers.path_to_east_texture)
		{
			free(data->identifiers.path_to_east_texture);
			data->duplicate_identifier = true;
		}
		data->identifiers.path_to_east_texture = ft_strdup(tmp[1]);
	}
}

static void	find_west_texture(t_file_data *data, const char **tmp)
{
	if (((tmp[0][0] == 'W' && !tmp[0][1]) || \
		!ft_strncmp("WE", tmp[0], 2)) && tmp[1])
	{
		if (data->identifiers.path_to_west_texture)
		{
			free(data->identifiers.path_to_west_texture);
			data->duplicate_identifier = true;
		}
		data->identifiers.path_to_west_texture = ft_strdup(tmp[1]);
	}
}

static void	find_south_texture(t_file_data *data, const char **tmp)
{
	if (((tmp[0][0] == 'S' && !tmp[0][1]) || \
		!ft_strncmp("SO", tmp[0], 2)) && tmp[1])
	{
		if (data->identifiers.path_to_south_texture)
		{
			free(data->identifiers.path_to_south_texture);
			data->duplicate_identifier = true;
		}
		data->identifiers.path_to_south_texture = ft_strdup(tmp[1]);
	}
}

static void	find_north_texture(t_file_data *data, const char **tmp)
{
	if (((tmp[0][0] == 'N' && !tmp[0][1]) || \
		!ft_strncmp("NO", tmp[0], 2)) && tmp[1])
	{
		if (data->identifiers.path_to_north_texture)
		{
			free(data->identifiers.path_to_north_texture);
			data->duplicate_identifier = true;
		}
		data->identifiers.path_to_north_texture = ft_strdup(tmp[1]);
	}
}

void	find_textures(const char *line, t_file_data *data)
{
	char	**tmp;

	tmp = ft_split(line, ' ');
	if (!tmp)
		return ;
	if (ft_strlen(tmp[0]) > 2)
	{
		free_2d(tmp);
		return ;
	}
	find_north_texture(data, (const char **)tmp);
	find_south_texture(data, (const char **)tmp);
	find_west_texture(data, (const char **)tmp);
	find_east_texture(data, (const char **)tmp);
	if (!check_identifiers_values(data, (const char **)tmp))
	{
		free_2d(tmp);
		return ;
	}
	free_2d(tmp);
}
