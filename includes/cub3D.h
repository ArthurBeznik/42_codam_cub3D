#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>
# include <MLX42.h>
# include <utils.h>
# include <parser.h>
# include <graphics.h>

typedef struct s_general_data
{
	t_file_data		file_data;
	t_graphics		graphics;
}	t_general_data;

int		main(int argc, char *argv[]);
bool	parser(int argc, char *argv[], t_general_data *data);
bool	init_file_data(t_general_data *data);
void	free_data(t_general_data *data);

bool	run_graphics(t_general_data	*data);

/**
 * Init. structs functions
*/
bool	init_graphics(t_general_data *data);
// bool	init_rays(t_general_data *data);
bool	init_textures(t_general_data *data);
bool	init_dda(t_general_data *data);
bool	init_calc(t_general_data *data);

/**
 * Draw functions
*/
bool	draw_square(t_general_data *data, int x, int y, uint32_t color, bool player);
bool	draw_line(t_general_data *data, int x, int y, t_axis axis);
bool	draw_player(t_general_data *data, mlx_image_t *img);
bool	draw_2d_map(t_general_data *data);
bool	check_put_pixel(t_general_data *data, uint32_t x, uint32_t y);

/**
 * Raycasting functions
*/
// bool	ray_caster(t_general_data *data);
// void	vertical_ray(t_general_data *data, t_ray *raymond, float angle, t_textures *textures);
// void	horizontal_ray(t_general_data *data, t_ray *raymond, float angle, t_textures *textures);

bool	dda(t_general_data *data);

/**
 * Misc. functions
*/
bool	fill_map(t_general_data	*data);
void	log_val(t_general_data *data, char *function, char values);

void    put_multi_pixels(mlx_image_t *img, unsigned color, int pixels, int offset);
unsigned int reverseBits(unsigned int num);

int	get_rgba(mlx_texture_t *texture, int x, int y);
void	draw_background(t_general_data *data);
void	init_ray_vars(t_general_data *data, int x);
void	calc_walls(t_general_data *data);
void	draw_3d(t_general_data *data, int x);
bool	cast_ray(t_general_data *data);

#endif
