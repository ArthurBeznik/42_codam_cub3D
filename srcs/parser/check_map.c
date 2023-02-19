/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:54:21 by edawood           #+#    #+#             */
/*   Updated: 2023/02/19 16:48:40 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

bool	check_map(char *file_name, t_file_data *file_data)
{
	file_data->fd = open(file_name, O_RDONLY);
	if (file_data->fd == ERROR)
		return (!error_msg("Opening scene file"));
	file_data->line = read_file(file_data);
	if (!file_data->line)
		return (!error_msg("Reading scene file"));
	if (!read_scene_file(file_data))
		return (!error_msg("Parsing scene file data"));
	if (!check_identifiers(file_data->identifiers, ".png"))
		return (!error_msg("Invalid identifiers"));
	return (true);
}
