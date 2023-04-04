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

# define ERROR -1
# define PIXELS 64
# define DR 0.0174533

# define H 10
# define V 11

# define ROTATION_SPEED 0.02
# define MOVE_SPEED 2.5
# define RESET_ANGLE 2 * M_PI

# define NB_RAYS 30

typedef struct s_general_data	t_general_data;

typedef struct s_ray
{
	float 	x;	// in pixels
	float 	y;	// in pixels
	float	angle;
	float 	off_y;
	float 	off_x;
	int		hit_x;	// in grid
	int		hit_y;	// in grid
	int		vx;
	int		vy;
	float 	dist_v;
	float 	dist_h;
}	t_ray;


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
	t_ray			**ray;
}	t_graphics;

bool	run_graphics(t_general_data	*data);
bool	init_graphics(t_general_data *data, t_graphics *graphics);

bool	loading_images(mlx_texture_t **textures);
bool	texture_to_image(t_graphics *graphics, mlx_texture_t **textures, \
													mlx_image_t **image);
bool	draw_2d_map(t_general_data *data);
bool	draw_square(t_general_data *data, int x, int y, uint32_t color, bool player);
bool	draw_line(t_general_data *data, int x, int y, int orientation);
bool	draw_player(t_general_data *data, mlx_image_t *img);

void	captain(void *param);

void	log_val(t_general_data *data, char *function, char values);
bool	check_put_pixel(t_general_data *data, uint32_t x, uint32_t y);
bool	fill_map(t_general_data	*data);
void	free_close_window(t_graphics *graphics, void *var, char *str);
void	terminate(t_graphics *graphics);

void	ray_casting(t_general_data *data);
bool	ray_caster(t_general_data *data);
bool	test_ray(t_general_data *data);

#endif