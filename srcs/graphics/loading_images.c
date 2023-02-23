/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_images.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:29:22 by edawood           #+#    #+#             */
/*   Updated: 2023/02/23 14:36:30 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphics.h>

bool    loading_images(mlx_texture_t **textures)
{
    textures[WALL] = mlx_load_png("path/to/wall.png");
    if (!textures[WALL])
        return (false);
    textures[PLAYER] = mlx_load_png("path/to/player.png");
    if (!textures[PLAYER])
        return (false);
    return (true);
}
