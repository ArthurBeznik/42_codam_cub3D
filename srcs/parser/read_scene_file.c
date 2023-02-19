/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:44:48 by edawood           #+#    #+#             */
/*   Updated: 2023/02/19 11:08:26 by edawood          ###   ########.fr       */
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