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

# define ERROR -1
# define NA 999

# define PIXELS 64
# define DR 0.0174533

# define ROT_SPEED 0.025
# define MOV_SPEED 0.05

# define RED 0xFF0000FF
# define GREEN 0x00FF00FF
# define BLUE 0x0000FFFF
# define YELLOW 0xFFFF00FF
# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define GREY 0x00000000

typedef struct s_general_data	t_general_data;

typedef enum e_side
{
	NORTH,
	WEST,
	SOUTH,
	EAST
}	t_side;

typedef enum e_axis
{
	HORIZONTAL,
	VERTICAL
}	t_axis;

typedef struct s_color
{
	unsigned int	rgba;
	int				r;
	int				g;
	int				b;
	int				a;
}	t_color;

typedef struct s_textures
{
	mlx_texture_t	*north_tex;
	mlx_texture_t	*south_tex;
	mlx_texture_t	*west_tex;
	mlx_texture_t	*east_tex;
	t_color			*floor;
	t_color			*ceiling;
	unsigned int	rgba;
}	t_textures;

typedef struct s_calc
{
	int		line_height;
	int		pitch;
	int		draw_start;
	int		draw_end;
	int		hit;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;
}	t_calc;

typedef struct s_draw
{
	float	x;
	float	y;
	float	step;
	float	dx;
	float	dy;
	float	x1;
	float	x2;
	float	y1;
	float	y2;	
}	t_draw;

typedef struct s_dda
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_dda;

typedef struct s_graphics
{
	mlx_t			*mlx;
	void			*win;
	int64_t			width;
	int64_t			height;
	mlx_image_t		*img;
	mlx_image_t		*img_3d;
	bool			init_dir;
	t_textures		textures;
	t_dda			dda;
	t_calc			calc;
	t_draw			draw;
}	t_graphics;

/**
 * Hook functions
*/
void	captain(void *param);
void	terminate(t_graphics *graphics, int code);
void	move_forward(t_general_data *data);
void	move_backward(t_general_data *data);
void	rotate_left(t_general_data *data);
void	rotate_right(t_general_data *data);

#endif