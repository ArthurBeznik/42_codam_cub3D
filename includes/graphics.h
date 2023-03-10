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

# define PIXELS 64
# define WIDTH 1920 // will be removed once we have a row length
# define HEIGHT 1080 // will be removed once we have rows count
# define PI 3.14159265358979323846
# define ERROR -1

typedef struct s_general_data	t_general_data;

typedef enum mlx_images
{
	IMG_FLOOR,
	IMG_CEILING,
	WALL,
	IMG_SPRITE,
	BG,
	PLAYER,
	IMG_COUNT
}	t_mlx_images;

typedef struct s_graphics
{
	mlx_t			*mlx;
	void			*win;
	int64_t			width;
	int64_t			height;
	mlx_image_t		*images[IMG_COUNT];
	mlx_texture_t	*textures[IMG_COUNT];
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
void	hook(void *param);

#endif