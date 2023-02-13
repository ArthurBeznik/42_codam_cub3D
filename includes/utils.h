/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/12 17:26:15 by abeznik       #+#    #+#                 */
/*   Updated: 2023/02/13 18:13:59 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3D.h"

int	exit_error(const char *message);

int	logger(const int code, const char *function, const char *message);

#endif
