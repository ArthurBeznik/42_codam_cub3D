/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_to_imgs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:39:43 by edawood           #+#    #+#             */
/*   Updated: 2023/02/23 14:42:09 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphics.h>

bool    texture_to_image(t_graphics *graphics, mlx_texture_t **textures, \
                                                    mlx_image_t **image)
{
    image[BG] = mlx_texture_to_image(graphics->mlx, textures[BG]);
    image[PLAYER] = mlx_texture_to_image(graphics->mlx, textures[PLAYER]);
    image[WALL] = mlx_texture_to_image(graphics->mlx, textures[WALL]);
    if (!image[BG] || !image[PLAYER] || !image[WALL])
        return (false);
    return (true);
}
