/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:54:15 by edawood           #+#    #+#             */
/*   Updated: 2023/02/22 19:44:24 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphics.h>

bool    init_mlx(t_graphics *graphics)
{
    graphics->mlx = mlx_init(graphics->width, graphics->height, "Cub3D", true);
    if (!graphics->mlx)
        return (false);
    graphics->textures[BG] = mlx_load_png("path/to/image.png");
    if (!graphics->textures[BG])
        return (false);
    graphics->images[BG] = mlx_texture_to_image(graphics->mlx, \
                                                graphics->textures[BG]);
    if (!graphics->images[BG])
        return (false);
    return (true);
}

bool    init_graphics(t_graphics *graphics)
{
    graphics->width = WIDTH * PIXELS;
    graphics->height = (HEIGHT * PIXELS) + PIXELS;
    if (!draw_background(graphics))
        return (false);
    if (mlx_image_to_window(graphics->mlx, graphics->images[BG], 200, 200) == ERROR)
    return (free_close_window(graphics, graphics->images[BG], \
                "image_to_window failed"), false);
    mlx_set_instance_depth(graphics->images[BG]->instances, -999);
    return (true);
}