/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_graphics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:18:49 by edawood           #+#    #+#             */
/*   Updated: 2023/02/22 16:19:29 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphics.h>

bool    run_graphics(t_graphics *graphics)
{
    if (!init_graphics(graphics))
        return (false);
    mlx_loop(graphics->mlx);
    return (true);
}