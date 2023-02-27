
#include <parser.h>

char *read_scene_file(t_file_data *data)
{
	char *buf;
	char	*tmp;

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
		buf[data->buflen] = '\0';
		// data->buflen = -1; // ? testing
		if (data->buflen == -1)
		{
			free(buf);
			free(data->line);
			return (NULL);
		}
		tmp = ft_strjoin(data->line, buf);
		// tmp = NULL; // ? testing
		if (!tmp)
		{
			free(buf);
			free(data->line);
			return (NULL);
		}
		data->line = ft_strdup(tmp);
		free(tmp);
	}
	// free(tmp);
	free(buf);
	close(data->fd);
	return (data->line);
}
