#ifndef GRAPHICS_H
# define GRAPHICS_H
# include <MLX42.h>
# include <stdbool.h>
# include <stdlib.h>
# include <libft.h>

# define PIXELS 64
# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.14159265358979323846
# define ERROR -1

typedef enum mlx_images
{
    IMG_FLOOR,
    IMG_CEILING,
    WALL,
    IMG_SPRITE,
    BG,
    PLAYER,
    IMG_COUNT
}               t_mlx_images;

typedef struct    s_graphics
{
    mlx_t		    *mlx;
    void		    *win;
    int64_t         width;
    int64_t         height;
    mlx_image_t     *images[IMG_COUNT];
    mlx_texture_t   *textures[IMG_COUNT];
}				t_graphics;

bool    run_graphics(t_graphics *graphics);
bool    init_graphics(t_graphics *graphics);
bool    draw_background(t_graphics *graphics);
bool    init_mlx(t_graphics *graphics);
void	free_close_window(t_graphics *graphics, void *var, char *str);
void	terminate(t_graphics *graphics);

#endif