/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:54:21 by edawood           #+#    #+#             */
/*   Updated: 2023/02/19 14:26:18 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

bool	check_map(char *file_name, t_file_data *file_data)
{
    file_data->fd = open(file_name, O_RDONLY);
    if (file_data->fd == ERROR)
        return (logger(EXIT_FAILURE, "check_map", "Error opening file"), false);
    file_data->line = read_file(file_data);
    if (!file_data->line)
        return (logger(EXIT_FAILURE, "check_map", "Error reading scene file"), false);
    if (!read_scene_file(file_data->line, file_data))
        return (logger(EXIT_FAILURE, "check_map", "Error spliting scene file"), false);
    return (true);
}