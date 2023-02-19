/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:44:48 by edawood           #+#    #+#             */
/*   Updated: 2023/02/19 17:27:53 by edawood          ###   ########.fr       */
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

char	**create_scene_map(t_file_data *data)
{
	int     i;
	int     j;
	char	**map;

	i = 0;
	j = 0;
	map = (char **) malloc(sizeof(char *) * (data->rows_count - 5));
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
	int i;

	i = 0;
	data->scene = ft_split(((const char *)data->line), '\n');
	data->rows_count = ft_count_rows(data->scene);
	if (!data->scene)
		return (false);
	while (i < data->rows_count)
	{
		find_identifier(data->scene[i], data);
		find_colors(data->scene[i], data);
		i++;
	}
	if (!check_scene_file_order(data))
	{
		error_msg("Invalid scene file order");
		free_2d(data->scene);
		return (false);
	}
	data->map_content = create_scene_map(data);
	if (!data->map_content)
	{
		error_msg("Invalid map");
		free_2d(data->scene);
		free_2d(data->map_content);
		return (false);
	}
	return (true);
}