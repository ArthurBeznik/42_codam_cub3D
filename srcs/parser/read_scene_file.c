/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:44:48 by edawood           #+#    #+#             */
/*   Updated: 2023/02/19 14:46:00 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

char	*read_file(t_file_data *data)
{
	char	*buf;

	data->line = ft_calloc(1, 1);
	if (!data->line)
		return (NULL);
	buf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
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

size_t	ft_count_rows(char **scene)
{
	size_t i;

	i = 0;
	while (scene[i])
		i++;
	return (i);
}

void	find_identifier(char *line, t_file_data *data)
{
	fprintf(stderr, "find_identifier: %s\n", line);
}

char	**read_scene_file(char *scene, t_file_data *data)
{
	int i;

	data->scene = ft_split(((const char *)data->line), '\n');
	data->rows_count = ft_count_rows(data->scene);
	if (!data->scene)
		return (NULL);
	
	i = 0;
	while (i < data->rows_count)
	{
		find_identifier(data->scene[i], data);
		fprintf(stderr, "read_scene_file: %s\n", data->scene[i]);
		i++;
	}
	return (data->scene);
}