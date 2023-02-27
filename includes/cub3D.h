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
# include "parser.h"
# include "graphics.h"

typedef struct s_general_data
{
	struct s_file_data		*file_data;
	struct s_graphics		*graphics;
}	t_general_data;

int		main(int argc, char *argv[]);

#endif
