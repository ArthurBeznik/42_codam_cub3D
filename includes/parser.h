
#ifndef PARSER_H
# define PARSER_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define ERROR -1

# include <cub3D.h>

bool	parser(int argc, char *argv[], t_file_data *file_data);
void	init_map_file_data(t_file_data *file_data);
bool	check_ext(char *file_name, char	*map_extension);
bool	check_map(char *file_name, t_file_data *file_data);
char	*read_file(t_file_data *data);
bool	read_scene_file(t_file_data *data);
bool	check_scene_file_order(t_file_data *data);
void	find_colors(char *line, t_file_data *data);
void	find_identifier(char *line, t_file_data *data);
void	free_2d(char **array);
size_t	ft_count_rows(char **scene);
bool	check_identifiers(t_identifiers_data *id_data, char *extension);
bool	check_map_content(char **map_content);

#endif
