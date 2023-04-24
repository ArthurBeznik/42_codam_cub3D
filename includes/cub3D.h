#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>
# include <MLX42.h>
# include <utils.h>
# include <parser.h>
# include <graphics.h>

typedef struct s_general_data
{
	t_file_data		file_data;
	struct s_graphics		*graphics;
}	t_general_data;

int		main(int argc, char *argv[]);
bool	parser(int argc, char *argv[], t_general_data *data);
bool	init_file_data(t_general_data *data);
void	free_data(t_general_data *data);

#endif
