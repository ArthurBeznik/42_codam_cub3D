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
# define RESET_ANGLE 2 * M_PI

// # define NB_RAYS 60
# define NB_RAYS 30

# define RED 0xFF0000FF
# define GREEN 0x00FF00FF
# define BLUE 0x0000FFFF
# define YELLOW 0xFFFF00FF
# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define GREY 0x00000000

typedef struct s_general_data	t_general_data;

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
	t_color			*floor;
	t_color			*ceiling;
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

/**
 * . dda:
 * 		always jumps exactly one square on each loop, either in the x-direction or the y-direction
 * 		loop that increments the ray with 1 square every time, until a wall is hit. 
 * 			Each time, either it jumps a square in the x-direction (with step_x) 
 * 			or a square in the y-direction (with step_y), it always jumps 1 square at once.
 * . camera plane has to be perpendicular to the direction, but the length of it can be changed
 * . ratio between the length of the direction and the camera plane determines the FOV
 * 		if direction vector > camera plane => smaller FOV 
 * 		if direction vector < camera plane => bigger FOV
 * 		=> FOV = (2 * atan(0.66 / 1.0) = 66 deg)	|| FOV = (2 * atan(0.66 / 1.0) = 66 deg)
 * . camera x:
 * 		right side of the screen	: coordinate = 1
 * 		center						: coordinate = 0
 * 		left						: coordinate = -1
 * . ray direction:
 * 		sum of direction vector and a part of the plane vector
 * 		both for x and y
 * . delta_dist:
 * 		we use Pythagore to calculate both values, and we can even change the formula to use 1 instead of |rayDir|, because only the *ratio* between deltaDistX and deltaDistY matters for the DDA code
 * 		if ray_dir_x or y is 0, to avoid dividing through 0 we set those to a very high value (1e30)
 * . side:
 * 		if x-side was hit	: side = 0
 * 		if y-side was hit	: side = 1
 * 		=> lines of the grid that are borders between two squares
 * . step:
 * 		if the ray dir has a negative x	: step_x = -1
 * 		if the ray dir has a positive x	: step_x = +1
 * 		if the ray dir has a 0 x		: step_x is unused
 * 		same for y
 * . side_dist:
 * 		if the ray dir has a negative x	: side_dist = dist from the ray starting position to the first side to the left
 * 		if the ray dir has a positive x	: step_x = +1
 * 		if the ray dir has a 0 x		: step_x is unused
 * 		here we use subtract the player position by the integer value map_x or map_y
 * 			and we add 1.0 if the side to the left or right, of the top or the bottom is used
 * 		this gives us the perpendicular distance to this side, we then have to multiply with delta_dist
 * 			to get the real euclidian distance
*/
typedef struct s_dda
{
	double	player_x;			// useless
	double	player_y;			// useless
	double	pos_x;				// player x position in grid values
	double	pos_y;				// player y position in grid values
	double	dir_x;				// player x direction
	double	dir_y;				// player y direction
	double	plane_x;			// player x camera plane
	double	plane_y;			// player y camera plane
	int		w;					// map width in grid values
	int		h;					// map height in grid values
	double	camera_x;			// x coord on the camera plane that the current x coord on the screen represents
	double	ray_dir_x;			// ray x direction (! in which square and where in the square)
	double	ray_dir_y;			// ray y direction (! in which square and where in the square)
	int		map_x;				// current square of the map the ray is in (! only the coord of the square, not where in the square)
	int		map_y;				// current square of the map the ray is in (! only the coord of the square, not where in the square)
	double	side_dist_x;		// initially, distance the ray has to travel from its start position to the first x-side, then incremented while steps are taken
	double	side_dist_y;		// initially, distance the ray has to travel from its start position to the first y-side, then incremented while steps are taken
	double	delta_dist_x;		// distance the ray has to travel to go from 1 x-side to the next x-side
	double	delta_dist_y;		// distance the ray has to travel to go from 1 y-side to the next y-side
	double	perp_wall_dist;		// used to calculate the length of the ray
	int		step_x;				// always either -1 or +1
	int		step_y;				// always either -1 or +1
	int		hit;				// determines if the coming loop has to be ended
	int		side;				// contains if an x-side or y-side of a wall was hit
}	t_dda;

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
	t_dda			*dda;
}	t_graphics;

bool	run_graphics(t_general_data	*data);

/**
 * Init. structs functions
*/
bool	init_graphics(t_general_data *data, t_graphics *graphics);
bool	init_rays(t_general_data *data);
bool	init_textures(t_general_data *data);
bool	init_dda(t_general_data *data);

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

bool	dda(t_general_data *data);

/**
 * Misc. functions
*/
bool	fill_map(t_general_data	*data);
void	log_val(t_general_data *data, char *function, char values);

#endif