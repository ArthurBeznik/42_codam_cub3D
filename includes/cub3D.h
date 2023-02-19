/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:05:21 by abeznik           #+#    #+#             */
/*   Updated: 2023/02/19 10:49:52 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>
# include <MLX42.h>

typedef struct file_data
{
    char    *map_extention;
    char    *line;
    int     fd;
    int     buflen;
}            t_file_data;

typedef struct s_general_data
{
    t_file_data     *file_data;
}            t_general_data;

# include <utils.h>
# include <parser.h>


int	main(int argc, char *argv[]);

#endif
