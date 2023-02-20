/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:06:24 by edawood           #+#    #+#             */
/*   Updated: 2023/02/19 17:15:21 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	find_colors(char *line, t_file_data *data)
{
	if (line[0] == 'F')
	{
		data->identifiers->floor->red = ft_atoi(line + 1);
		data->identifiers->floor->green = ft_atoi(line + 3);
		data->identifiers->floor->blue = ft_atoi(line + 5);
	}
	else if (line[0] == 'C')
	{
		data->identifiers->ceiling->red = ft_atoi(line + 1);
		data->identifiers->ceiling->green = ft_atoi(line + 3);
		data->identifiers->ceiling->blue = ft_atoi(line + 5);
	}
}

bool	check_scene_file_order(t_file_data *data)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if (data->scene[i][0] == '1')
			return (error_msg("Scene file starts with map content"), false);
		i++;
	}
	if (data->scene[data->rows_count - 1][0] != '1')
		return (error_msg("Scene file does not end with map content"), false);
	return (true);
}
