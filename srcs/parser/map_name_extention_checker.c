/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extention.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:33:38 by edawood           #+#    #+#             */
/*   Updated: 2023/02/15 17:12:36 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

bool	check_ext(char *file_name, t_file_data *file_data)
{
	size_t	ext_len;
	size_t	name_len;

	if (!file_data->map_extention)
		return (logger(EXIT_FAILURE, "check_ext", \
				"You are not checking for an extension"), false);
	if (!file_name)
		return (logger(EXIT_FAILURE, "check_ext", \
				"There is no file name"), false);
	ext_len = ft_strlen(file_data->map_extention);
	name_len = ft_strlen(file_name);
	while (ext_len > 0)
	{
		if (file_name[name_len--] != file_data->map_extention[ext_len--])
			return (logger(EXIT_FAILURE, "check_ext", \
					"Wrong file extension"), false);
	}
	return (true);
}