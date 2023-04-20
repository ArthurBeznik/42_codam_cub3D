// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   draw_3d_map.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/12/08 18:11:35 by ydemura           #+#    #+#             */
// /*   Updated: 2023/04/13 19:56:22 by edawood          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3D.h"

// unsigned int	color_maker(int red, int green, int blue)
// {
// 	unsigned int	alpha;
// 	unsigned int	res;

// 	alpha = 255;
// 	res = 0;
// 	if ((red >= 0 && red <= 255) && (green >= 0 && green <= 255)
// 		&& (blue >= 0 && blue <= 255))
// 		res = ((unsigned int)(red << 24 | green << 16 | blue << 8 | alpha));
// 	else
// 		return 0;
// 	return (res);
// }

// static int	get_rgba(mlx_texture_t *texture, int x, int y)
// {
// 	int	r;
// 	int	g;
// 	int	b;
// 	int	a;

// 	r = texture->pixels[y * texture->width * 4 + (x * 4)];
// 	g = texture->pixels[y * texture->width * 4 + (x * 4) + 1];
// 	b = texture->pixels[y * texture->width * 4 + (x * 4) + 2];
// 	a = texture->pixels[y * texture->width * 4 + (x * 4) + 3];
// 	return (r << 24 | g << 16 | b << 8 | a);
// }

// void	draw_ceiling_and_floor(t_general_data *data, int i)
// {
// 	int	half;
// 	int	start;
// 	// unsigned int	color_ceiling;
// 	// unsigned int	color_floor;

// 	start = 0;
// 	half = (SCREENHEIGHT - start) / 2;

// 	// color_ceiling = color_maker(data->file_data->identifiers->ceiling->red,
// 	// 		data->file_data->identifiers->ceiling->green,
// 	// 		data->file_data->identifiers->ceiling->blue);
// 	// color_floor = color_maker(data->file_data->identifiers->floor->red,
// 	// 		data->file_data->identifiers->floor->green,
// 	// 		data->file_data->identifiers->floor->blue);
	
// 	while (start < SCREENHEIGHT)
// 	{
// 		if (start < half)
// 			mlx_put_pixel(data->graphics->img, i, start, data->file_data->identifiers->ceiling->rgba);
// 		else
// 			mlx_put_pixel(data->graphics->img, i, start, data->file_data->identifiers->floor->rgba);
// 		start++;
// 	}
// }

// void	fill_info(t_draw_info *info, t_general_data *data, double height)
// {
// 	if (data->file_data->player->facing == 'N')
// 		info->tex = data->graphics->textures_3d[NORTH];
// 	else if (data->file_data->player->facing == 'S')
// 		info->tex = data->graphics->textures_3d[SOUTH];
// 	else if (data->file_data->player->facing == 'E')
// 		info->tex = data->graphics->textures_3d[EAST];
// 	else if (data->file_data->player->facing == 'W')
// 		info->tex = data->graphics->textures_3d[WEST];
// 	else
// 		return ;
// 	if (height >= data->graphics->img->height)
// 	{
// 		info->top = 0;
// 		info->bottom = data->graphics->img->height - 1;
// 		info->text_start = (((1 - (1.0 * data->graphics->img->height / height)) / 2.0)
// 				* info->tex->height);
// 	}
// 	else
// 	{
// 		info->top = (data->graphics->img->height - height) / 2;
// 		info->bottom = (data->graphics->img->height + height) / 2;
// 		info->text_start = 0.0;
// 	}
// 	info->step = 1.0 * info->tex->height / height;
// }

// void	draw_3d_map(t_general_data *data, t_ray *raymond, int i)
// {
// 	double		height;
// 	int			x;
// 	t_draw_info	info;

// 	height = (PIXELS * 320) / (raymond->dist_h);
// 	x = 0;
// 	fill_info(&info, data, height);
// 	draw_ceiling_and_floor(data, i);
// 	while (x < info.bottom - info.top)
// 	{
// 		if (data->file_data->player->facing == 'E' || data->file_data->player->facing == 'N')
// 			info.color = get_rgba(info.tex,
// 					((unsigned int)((1.0 - data->file_data->player->x)
// 							* info.tex->width)),
// 					((unsigned int)(info.text_start + x * info.step)));
// 		else
// 			info.color = get_rgba(info.tex,
// 					((unsigned int)((data->file_data->player->x) * info.tex->width)),
// 					((unsigned int)(info.text_start + x * info.step)));
// 		mlx_put_pixel(data->graphics->img, i, x + info.top, info.color);
// 		x++;
// 	}
// 	i++;
// }
