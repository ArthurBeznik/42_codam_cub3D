/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3D.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/12 17:05:21 by abeznik       #+#    #+#                 */
/*   Updated: 2023/02/19 11:57:21 by abeznik       ########   odam.nl         */
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

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

typedef struct s_identifiers_data
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	t_rgb	*floor;
	t_rgb	*ceiling;

}	t_identifiers_data;

typedef struct s_file_data
{
	char	*map_extension;
	char	*line;
	int		fd;
	int		buflen;
	t_identifiers_data	*identifiers;
}	t_file_data;

typedef struct s_general_data
{
	t_file_data	*file_data;
}	t_general_data;

/**
 * ? this causes a norminette error => includes should be at the beginning
*/
# include <utils.h>
# include <parser.h>

int	main(int argc, char *argv[]);

#endif
