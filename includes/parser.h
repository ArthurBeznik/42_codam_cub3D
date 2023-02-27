#ifndef PARSER_H
# define PARSER_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define ERROR -1

# define Y 888
# define X 777

# include <cub3D.h>

typedef struct s_player
{
	int64_t		x;
	int64_t		y;
	char		facing;
}	t_player;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

typedef struct s_identifiers_data
{
	char	*path_to_north_texture;
	char	*path_to_south_texture;
	char	*path_to_west_texture;
	char	*path_to_east_texture;
	t_rgb	*floor;
	t_rgb	*ceiling;

}	t_identifiers_data;

typedef struct map_data
{
	int64_t		rows_count;
	char		**map;
	char		**copy;
	t_player	*player;
}	t_map_data;

typedef struct s_file_data
{
	char				*file_extension;
	char				**scene;
	t_map_data			*map_data;
	char				*line;
	int					fd;
	int					buflen;
	t_identifiers_data	*identifiers;
}	t_file_data;

bool	parser(int argc, char **argv, t_file_data *file_data);
void	init_map_file_data(t_file_data *file_data);
bool	check_ext(char *file_name, char	*file_extension);
bool	check_map(char *file_name, t_file_data *file_data);
char	*read_scene_file(t_file_data *data);
bool	read_scene_data(t_file_data *data);
bool	check_scene_file_order(t_file_data *data);
void	find_colors(char *line, t_file_data *data);
void	find_identifier(char *line, t_file_data *data);
bool	check_identifiers(t_identifiers_data *id_data, char *extension);
bool	check_map_content(char **map);
bool	check_walls(t_map_data *map_data);
void	flood_fill(int y, int x, t_map_data *map_data, bool *is_enclosed);

#endif
