
#include <parser.h>

char *read_file(t_file_data *data)
{
	char *buf;

	data->line = ft_calloc(1, 1);
	// data->line = NULL; // ? testing calloc failure => does not segfault
	if (!data->line)
		return (NULL);
	buf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	// buf = NULL; // ? testing calloc failure => does not segfault
	if (!buf)
		return (free(data->line), NULL);
	while (data->buflen > 0)
	{
		data->buflen = read(data->fd, buf, BUFFER_SIZE);
		if (data->buflen == -1)
		{
			free(data->line);
			free(buf);
			return (NULL);
		}
		data->line = ft_strjoin(data->line, buf);
	}
	free(buf);
	close(data->fd);
	return (data->line);
}

char	**create_scene_map(t_file_data *data)
{
	size_t	i;
	size_t	j;
	char	**map;

	i = 0;
	j = 0;
	map = (char **)malloc(sizeof(char *) * (data->rows_count - 5));
	// map = NULL; // ? testing malloc failure =>  => does not segfault
	if (!map)
		return (NULL);
	while (i < data->rows_count)
	{
		if (i >= 6)
		{
			map[j] = ft_strdup(data->scene[i]);
			j++;
		}
		i++;
	}
	map[j] = NULL;
	return (map);
}

bool	read_scene_file(t_file_data *data)
{
	size_t i;

	i = 0;
	data->scene = ft_split(((const char *)data->line), '\n');
	// data->scene = NULL; // ? testing split failure  => does not segfault
	if (!data->scene)
		return (false);
	data->rows_count = ft_count_rows(data->scene);
	// data->rows_count = NULL; // ? testing count_rows failure  => does not segfault
	if (!data->rows_count)
		return (false);
	while (i < data->rows_count)
	{
		find_identifier(data->scene[i], data);
		find_colors(data->scene[i], data);
		i++;
	}
	// if (!check_scene_file_order(data))
	// {
	// 	free_2d(data->scene);
	// 	return (error_msg("Invalid scene file order"));
	// }
	data->map_content = create_scene_map(data);
	if (!data->map_content)
	{
		free_2d(data->scene);
		// free_2d(data->map_content); // ? if data->map_content is NULL => cant free it => SEGFAULT
		return (error_msg("Invalid map"));
	}
	return (true);
}