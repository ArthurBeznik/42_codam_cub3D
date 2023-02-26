/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:44:13 by edawood           #+#    #+#             */
/*   Updated: 2023/02/22 19:44:29 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphics.h>

bool    draw_background(t_graphics *graphics)
{
    int     x;
    int     y;
    int     color;

    y = 0;
    color = 0x000000;
    if (!init_mlx(graphics))
        return (false);
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
			mlx_image_to_window(graphics->mlx, graphics->images[BG], \
								x * PIXELS, y * PIXELS);
			if (! mlx_image_to_window(graphics->mlx, \
			graphics->images[BG], x * PIXELS, y * PIXELS))
				return (false);
			x++;
        }
        y++;
    }
    return (true);
}
