#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>
# include <MLX42.h>
# include <utils.h>
# include <math.h>

# define PIXELS 64
# define WIDTH 1920 // will be removed once we have a row length
# define HEIGHT 1080 // will be removed once we have rows count
# define PI 3.14159265358979323846
# define ERROR -1

# define H 10
# define V 11

typedef struct s_general_data	t_general_data;

typedef enum mlx_images
{
	IMG_FLOOR,
	IMG_CEILING,
	WALL,
	IMG_SPRITE,
	BG,
	PLAYER,
	LINE,
	IMG_COUNT
}	t_mlx_images;

typedef struct s_graphics
{
	mlx_t			*mlx;
	void			*win;
	int64_t			width;
	int64_t			height;
	mlx_image_t		*img;
	mlx_texture_t	*textures[IMG_COUNT];
	bool			init_dir;
}	t_graphics;

bool	run_graphics(t_general_data	*data);
bool	init_graphics(t_general_data *data, t_graphics *graphics);
bool	draw_background(t_graphics *graphics);
bool	init_mlx(t_general_data	*data, t_graphics *graphics);
void	free_close_window(t_graphics *graphics, void *var, char *str);
void	terminate(t_graphics *graphics);
bool	loading_images(mlx_texture_t **textures);
bool	texture_to_image(t_graphics *graphics, mlx_texture_t **textures, \
													mlx_image_t **image);
void	captain(void *param);
bool	map_viewer(t_general_data *data);
void	draw_square(mlx_image_t* img, int x, int y, uint32_t color, bool player);
void	draw_line(mlx_image_t* img, int x, int y, int orientation);

bool	ray_caster(t_general_data *data);

void	log_positions(t_general_data *data, char player_or_image, char *message);

void	draw_2d_map(t_general_data *data, mlx_image_t *img);

void	draw_player(t_general_data *data, mlx_image_t *img);

#endif