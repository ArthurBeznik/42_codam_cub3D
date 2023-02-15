/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:04:23 by abeznik           #+#    #+#             */
/*   Updated: 2023/02/15 17:22:24 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <cub3D.h>

bool	parser(int argc, char *argv[], t_general_data *data);
void	init_map_file_data(t_file_data *file_data);
bool	check_ext(char *file_name, t_file_data *file_data);

#endif
