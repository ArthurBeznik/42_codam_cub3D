/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/12 17:26:15 by abeznik       #+#    #+#                 */
/*   Updated: 2023/02/19 14:31:38 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <cub3D.h>

bool	error_msg(const char *message);

int	logger(const int code, const char *function, const char *message);

#endif
