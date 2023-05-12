#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <stdlib.h>
# include <libft.h>
# define ERROR -1

bool	error_msg(const char *message);
int		logger(const int code, const char *function, const char *message);
void	print_map(const char **map);
void	free_2d(char **array);
int		ft_count_rows(const char **scene);
int		get_max_line_len(const char **map);
bool	is_player(const char c);
char	**copy_map(char **map, int rows);

#endif
