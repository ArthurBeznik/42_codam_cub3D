#ifndef UTILS_H
# define UTILS_H

# include <cub3D.h>

bool	error_msg(const char *message);

int		logger(const int code, const char *function, const char *message);

void	print_map(char **map);

void	free_2d(char **array);

int		ft_count_rows(const char **scene);

#endif
