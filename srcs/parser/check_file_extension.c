/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_extension.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 12:33:38 by edawood       #+#    #+#                 */
/*   Updated: 2023/02/19 14:43:11 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

/**
 * maybe we can pass the map extension directly instead of the whole struct
 * this way I can reuse this to check if the identifiers have png
 * 	OR
 * can we just verfiy the filename directly against ".cub" as its always going to be that
*/
bool	check_ext(char *file_name, char	*extension)
{
	size_t	ext_len;
	size_t	name_len;

	if (!extension)
		return (error_msg("No extension given"));
	if (!file_name)
		return (error_msg("No file name given"));
	ext_len = ft_strlen(extension);
	name_len = ft_strlen(file_name);
	while (ext_len > 0)
	{
		if (file_name[name_len--] != extension[ext_len--])
			return (error_msg("Incorrect file extension"));
	}
	return (true);
}
