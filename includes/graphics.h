#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>
# include <math.h>

# include <utils.h>
# include <MLX42.h>
# define SCREENWIDTH 1000
# define SCREENHEIGHT 1000

# define ERROR -1
# define NA 999

# define PIXELS 64
# define DR 0.0174533

# define ROT_SPEED 0.01
# define MOV_SPEED 1.2
# define RESET_ANGLE 2 * M_PI

# define NB_RAYS 30

# define RED 0xFF0000FF
# define GREEN 0x00FF00FF
# define BLUE 0x0000FFFF
# define YELLOW 0xFFFF00FF
# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define GREY 0x00000000

typedef struct s_general_data	t_general_data;

typedef union s_rgba_color
{
	unsigned int	rgba;
	struct
	{
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	};
	
}	t_rgba_color;

typedef enum e_axis
{
	HORIZONTAL,
	VERTICAL
}	t_axis;

typedef enum e_side
{
	EAST = 0,
	SOUTH = 1,
	WEST = 2,
	NORTH =3
}	t_side;

// typedef struct s_color
// {
// 	unsigned int	rgba;
// 	int				r;
// 	int				g;
// 	int				b;
// 	int				a;
// }	t_color;

typedef struct s_textures
{
	int				vmt; // vertical and horizontal map texture number (= color value)
	int				hmt;
	float			shade;
	float			x;
	float			y;
	float			y_step;
	float			y_off;
	mlx_texture_t	*north_tex;
	mlx_texture_t	*south_tex;
	mlx_texture_t	*west_tex;
	mlx_texture_t	*east_tex;
	t_rgba_color	floor;
	t_rgba_color	ceiling;
	unsigned int	rgba;
}	t_textures;

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
	float	tan_var;
	int		dof;
}	t_ray;

typedef struct s_wall_collision
{
	int		xo;
	int		yo;
	int		ipx;
	int		ipx_add_xo;
	int		ipx_sub_xo;
	int		ipy;
	int		ipy_add_yo;
	int		ipy_sub_yo;
}	t_wall_collision;

typedef struct s_draw_info
{
	int				top;
	int				bottom;
	unsigned int	color;
	double			step;
	mlx_texture_t	*tex;
	double			text_start;
}					t_draw_info;

typedef struct s_graphics
{
	mlx_t			*mlx;
	mlx_t			*mlx_3d;
	void			*win;
	int64_t			width;
	int64_t			height;
	mlx_image_t		*img;
	mlx_image_t		*img_3d;
	bool			init_dir;
	t_ray			**ray;
	t_textures		*textures;
	t_draw_info		*draw_info;
}	t_graphics;


bool	run_graphics(t_general_data	*data);

/**
 * Init. structs functions
*/
bool	init_graphics(t_general_data *data, t_graphics *graphics);
bool	init_rays(t_general_data *data);
bool	init_textures(t_general_data *data);

/**
 * Draw functions
*/
bool	draw_square(t_general_data *data, int x, int y, uint32_t color, bool player);
bool	draw_line(t_general_data *data, int x, int y, t_axis axis);
bool	draw_player(t_general_data *data, mlx_image_t *img);
bool	draw_2d_map(t_general_data *data);
bool	check_put_pixel(t_general_data *data, uint32_t x, uint32_t y);

/**
 * Hooks functions
*/
void	captain(void *param);
void	free_close_window(t_graphics *graphics, void *var, char *str);
void	terminate(t_graphics *graphics);

/**
 * Raycasting functions
*/
bool	ray_caster(t_general_data *data);
void	vertical_ray(t_general_data *data, t_ray *raymond, float angle, t_textures *textures);
void	horizontal_ray(t_general_data *data, t_ray *raymond, float angle, t_textures *textures);

/**
 * Misc. functions
*/
bool	fill_map(t_general_data	*data);
void	log_val(t_general_data *data, char *function, char values);

#endif