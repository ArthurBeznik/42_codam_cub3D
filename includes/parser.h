#ifndef PARSER_H
# define PARSER_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define ERROR -1
# define NA 999

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>
# include <MLX42.h>
# include <utils.h>

typedef struct s_player
{
	float		x;
	float		y;
	float		dx;
	float		dy;
	float		angle;
	char		facing;
	double		px;
	double		py;
}	t_player;

typedef union s_rgb
{
	unsigned int	rgba;
	struct
	{
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	};
}	t_rgb;

typedef struct s_identifiers_data
{
	char	*path_to_north_texture;
	char	*path_to_south_texture;
	char	*path_to_west_texture;
	char	*path_to_east_texture;
	t_rgb	floor;
	t_rgb	ceiling;

}	t_identifiers_data;

typedef struct map_data
{
	int64_t		row;
	int64_t		col;
	char		**map;
	char		**copy;
}	t_map_data;

typedef struct s_file_data
{
	char				*file_extension;
	char				**scene;
	char				*line;
	char				*red;
	char				*green;
	char				*blue;
	int					fd;
	int					buflen;
	bool				ceiling_found;
	bool				floor_found;
	bool				duplicate_identifier;
	bool				duplicate_color;
	bool				only_texture_id;
	t_map_data			map_data;
	t_identifiers_data	identifiers;
	t_player			player;
}	t_file_data;

bool	check_ext(const char *file_name, const char *file_extension);
bool	check_map(const char *file_name, t_file_data *file_data);
bool	read_scene_data(t_file_data *data);
bool	check_identifiers(t_identifiers_data *id_data, const char *extension);
bool	check_map_content(const char **map);
bool	check_walls(t_file_data *data);
char	*read_scene_file(t_file_data *data);
void	find_textures(const char *line, t_file_data *data);
bool	check_identifiers(t_identifiers_data *id_data, const char *extension);
bool	check_identifiers_values(t_file_data *data, const char **tmp);
bool	find_colors(const char *line, t_file_data *data);
bool	check_color_range(const int r, const int g, const int b);
bool	check_rgb_values(const char **rgb_values);
bool	check_scene_file_order(t_file_data *data);
void	flood_fill(const int y, const int x, t_map_data *map_data, \
	bool *is_enclosed);
void	free_2d(char **array);
void	free_colors_helpers(char *red, char *green, char *blue);

#endif
