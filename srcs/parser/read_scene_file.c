#include <parser.h>

char	*init_line_buf(t_file_data *data)
{
	char	*buf;

	data->line = ft_calloc(1, 1);
	// data->line = NULL; // ? testing
	if (!data->line)
		return (NULL);
	buf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buf)
		return (free(data->line), NULL);
	return (buf);
}

bool	join_save_line(t_file_data *data, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(data->line, buf);
	if (!tmp)
		return (false);
	data->line = ft_strdup(tmp);
	if (!data->line)
	{
		free(tmp);
		return (false);
	}
	free(tmp);
	return (true);
}

char *read_scene_file(t_file_data *data)
{
	char *buf;

	buf = init_line_buf(data);
	if (!buf)
		return (NULL);
	while (data->buflen > 0)
	{
		data->buflen = read(data->fd, buf, BUFFER_SIZE);
		buf[data->buflen] = '\0';
		if (data->buflen == -1)
		{
			free(buf);
			return (NULL);
		}
		if (!join_save_line(data, buf))
			return (NULL);
	}
	free(buf);
	close(data->fd);
	return (data->line);
}
