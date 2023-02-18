/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:56:05 by abeznik           #+#    #+#             */
/*   Updated: 2023/02/15 17:22:07 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	init_map_file_data(t_file_data *file_data)
{
	file_data->map_extention = ".cub";
}

bool	parser(int argc, char *argv[], t_general_data *data)
{
	t_file_data file_data;

	init_map_file_data(&file_data);
	if (argc != 2)
		return (false);
	if (!check_ext(argv[1], &file_data))
		return (false);
	return (true);
}
