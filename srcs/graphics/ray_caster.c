#include <graphics.h>

/**
 * the index of the pixel at (x, y) in the pixels array is calculated by 
 * multiplying the y-coordinate by the width of the texture in pixels, 
 * and adding the product of the x-coordinate and four 
 * (which represents the number of bytes per pixel).
 * 
 * Then, the r, g, b, and a values are obtained by adding the appropriate 
 * offset to this index: 0 for red, 1 for green, 2 for blue, and 3 for alpha.
*/
static int	get_rgba(mlx_texture_t *texture, int x, int y)
{
	int	r;
	int	g;
	int	b;
	int	a;

	// fprintf(stderr, "x | y : %d | %d\n", x, y); // ? testing
	r = texture->pixels[y * texture->width * 4 + (x * 4)];
	g = texture->pixels[y * texture->width * 4 + (x * 4) + 1];
	b = texture->pixels[y * texture->width * 4 + (x * 4) + 2];
	a = texture->pixels[y * texture->width * 4 + (x * 4) + 3];
	// fprintf(stderr, "r: %d | g: %d | b: %d | a: %d\n", r,g , b, a); // ? testing
	return (r << 24 | g << 16 | b << 8 | a);
}

bool	draw_3d_walls(t_general_data *data, t_ray *raymond, int i, t_textures *textures)
{
	float	ca;
	int		line_h;
	int		line_off;
	int		n;
	int		x1;
	int		y1;

	/**
	 * ! fixing fish eye
	 * 	ca: angle between the player's direction and the ray's direction
	 * 	dist_h: horizontal distance between the player and the wall the ray hits
	 *  line_h: height of the wall that the ray hits
	 * 	line_off: offset from the center of the screen to the top of the wall
	 * 		If the wall is taller, the offset will be negative and the wall will start off the screen at the top. 
	 * 		If the wall is shorter, the offset will be positive and the wall will start on the screen.
	*/
	ca = data->file_data->player->angle - raymond->angle;
	// fprintf(stderr, "[draw_3d_walls]\tca: %f\n", ca); // ? testing
	// fprintf(stderr, "[draw_3d_walls]\tpa: %f\n", data->file_data->player->angle); // ? testing
	// fprintf(stderr, "[draw_3d_walls]\tra: %f\n", raymond->angle); // ? testing
	if (ca < 0)
		ca += RESET_ANGLE;
	if (ca > 2 * M_PI)
		ca -= RESET_ANGLE;
	raymond->dist_h = raymond->dist_h * cos(ca);
	line_h = (PIXELS * 320) / (raymond->dist_h);

	textures->y_step = 64.0 / (float)line_h; // ! wall height / line height
	textures->y_off = 0; // !
	
	if (line_h > 320)
	{
		textures->y_off = (line_h - 320) / 2.0; // !
		line_h = 320;
	}
	line_off = 160 - (line_h >> 1);

	// fprintf(stderr, "[draw_3d_walls]\tline_off: %d\n", line_off); // ? testing

	// ! textures->y = textures->y_off * textures->y_step + textures->hmt * 64; // ! read next texture
	textures->y = textures->y_off * textures->y_step; // ! 
	// fprintf(stderr, "ty: %f\n", textures->y);
	if (textures->shade == 1)
	{
		textures->x = (int)(raymond->x) % 64;
		if (raymond->angle > M_PI) // ! flip the texture if we are looking south
		{
			textures->x = 63 - textures->x;
		}
		// fprintf(stderr, "tx: %f\n", textures->x);
	}
	else
	{
		textures->x = (int)(raymond->y) % 64;
		if (raymond->angle > (M_PI / 2) && raymond->angle < (3 * M_PI / 2)) // ! flip the texture if we are looking south
		{
			textures->x = 63 - textures->x;
		}
		// fprintf(stderr, "tx: %f\n", textures->x);
	}


	/* draw walls */
	n = 0;
	while (n < line_h)
	{
		// ! int c = data->graphics->textures->north_tex->pixels[(int)textures->y*64 + (int)textures->x];
		// fprintf(stderr, "c: %f\n", c);
		// fprintf(stderr, "hmt | vmt : %d | %d\n", textures->hmt, textures->vmt);
		// fprintf(stderr, "rgba: %d\n", rgba);
		if (textures->hmt == 0)
		{
			textures->rgba = get_rgba(data->graphics->textures->north_tex, (int)textures->x, (int)textures->y);
		} // red
		if (textures->hmt == 1)
		{
			textures->rgba = get_rgba(data->graphics->textures->south_tex, (int)textures->x, (int)textures->y);
		} // yellow
		if (textures->hmt == 2)
		{
			textures->rgba = get_rgba(data->graphics->textures->west_tex, (int)textures->x, (int)textures->y);
		} // blue
		if (textures->hmt == 3)
		{
			textures->rgba = get_rgba(data->graphics->textures->east_tex, (int)textures->x, (int)textures->y);
		} // green

		// log_val(data, "draw_3d_walls", 'A');
		x1 = i * 8; // ! on x, draw every 8th pixel
		y1 = line_off + n; // ! on y, starting at line_off, draw every n pixels until line_h
		// fprintf(stderr, "[draw_3d_walls]\tx1 | y1: %d | %d\n", x1, y1); // ? testing
		// log_val(data, "draw_3d_walls", 'D'); // ? testing
		// log_val(data, "draw_3d_walls", 'P'); // ? testing
		// fprintf(stderr, "shade: %f\n", textures->shade);

		if (!check_put_pixel(data, x1, y1))
			return (false);
		// if (textures->shade != 1)
		// 	mlx_put_pixel(data->graphics->img_3d, x1, y1, GREEN);
		// else
		// 	mlx_put_pixel(data->graphics->img_3d, x1, y1, RED);
		// mlx_put_pixel(data->graphics->img_3d, x1, y1, textures->color);
		mlx_put_pixel(data->graphics->img_3d, x1, y1, textures->rgba);
		mlx_put_pixel(data->graphics->img_3d, x1 + 1, y1, textures->rgba);
		mlx_put_pixel(data->graphics->img_3d, x1 + 2, y1, textures->rgba);
		mlx_put_pixel(data->graphics->img_3d, x1 + 3, y1, textures->rgba);
		mlx_put_pixel(data->graphics->img_3d, x1 + 4, y1, textures->rgba);
		mlx_put_pixel(data->graphics->img_3d, x1 + 5, y1, textures->rgba);
		mlx_put_pixel(data->graphics->img_3d, x1 + 6, y1, textures->rgba);
		mlx_put_pixel(data->graphics->img_3d, x1 + 7, y1, textures->rgba);

		textures->y += textures->y_step;
		n++;
	}

	/* draw ceiling and floor */
	n = line_off + line_h;
	while (n < 320)
	{
		/* draw floor */
		float dy = n - (320 / 2.0);
		float deg = raymond->angle;
		float raFix = cos(data->file_data->player->angle - raymond->angle);
		textures->x = data->file_data->player->x / 2 + cos(deg) * 158 * 64 / dy / raFix;
		textures->y = data->file_data->player->y / 2 - sin(deg) * 158 * 64 / dy / raFix;
		x1 = i * 8;
		y1 = n;

		// int mp = mapF[(int)(ty / 32.0) * mapX + (int)(tx / 32.0)] * 32 * 32; // !
		// float c = All_Textures[((int)(ty)&31) * 32 + ((int)(tx)&31) + mp] * 0.7; // !

		if (!check_put_pixel(data, x1, y1))
			return (false);
		mlx_put_pixel(data->graphics->img_3d, x1, y1, GREEN);
		// mlx_put_pixel(data->graphics->img_3d, x1 + 1, y1, WHITE);
		// mlx_put_pixel(data->graphics->img_3d, x1 + 2, y1, WHITE);
		// mlx_put_pixel(data->graphics->img_3d, x1 + 3, y1, WHITE);
		// mlx_put_pixel(data->graphics->img_3d, x1 + 4, y1, WHITE);
		// mlx_put_pixel(data->graphics->img_3d, x1 + 5, y1, WHITE);
		// mlx_put_pixel(data->graphics->img_3d, x1 + 6, y1, WHITE);
		// mlx_put_pixel(data->graphics->img_3d, x1 + 7, y1, WHITE);

		/* draw ceiling */

		// mp = mapC[(int)(ty / 32.0) * mapX + (int)(tx / 32.0)] * 32 * 32; // !
		// c = All_Textures[((int)(ty)&31) * 32 + ((int)(tx)&31) + mp] * 0.7; // !
		
		x1 = i * 8;
		y1 = 320 - n;
		if (!check_put_pixel(data, x1, y1))
			return (false);
		mlx_put_pixel(data->graphics->img_3d, x1, y1, BLUE);
		// mlx_put_pixel(data->graphics->img_3d, x1 + 1, y1, BLACK);
		// mlx_put_pixel(data->graphics->img_3d, x1 + 2, y1, BLACK);
		// mlx_put_pixel(data->graphics->img_3d, x1 + 3, y1, BLACK);
		// mlx_put_pixel(data->graphics->img_3d, x1 + 4, y1, BLACK);
		// mlx_put_pixel(data->graphics->img_3d, x1 + 5, y1, BLACK);
		// mlx_put_pixel(data->graphics->img_3d, x1 + 6, y1, BLACK);
		// mlx_put_pixel(data->graphics->img_3d, x1 + 7, y1, BLACK);
		n++;
	}
	return (true);
}

bool	draw_ray(t_general_data *data, double angle, float x, float y)
{
	int		i;
	float	x1;
	float	y1;
	float	ray_len;

	i = 0;
	x1 = 0;
	y1 = 0;
	// ray_len = sqrt(pow(x - data->file_data->player->x, 2) + pow(y - data->file_data->player->y, 2));		 // ! these two ray_len give the same result
	ray_len = cos(angle) * (x - data->file_data->player->x) - sin(angle) * (y - data->file_data->player->y); // ! these two ray_len give the same result
	// fprintf(stderr, "[draw_ray]\tray_len: %f\n", ray_len); // ? testing
	// fprintf(stderr, "[draw_ray]\trounded ray_len: %f\n", roundf(ray_len)); // ? testing
	// fprintf(stderr, "[draw_ray]\t rx | ry : %d | %d\n", x, y); // ? testing
	while (i < roundf(ray_len)) // ! stops on the wall
	// while (i < ray_len) // ! stops after the wall ~= 1px
	// while (i < ray_len - 1) // ! stops before the wall ~= 1px
	{
		x1 = round(i * cos((angle))) + (data->file_data->player->x); // ! this need to be rounded, like x and _y to have grid values
		y1 = round(i * -sin((angle))) + (data->file_data->player->y); // ! this need to be rounded, like x and _y to have grid values
		// log_val(data, "draw_ray", 'D'); // ? testing
		// log_val(data, "draw_ray", 'P'); // ? testing
		// fprintf(stderr, "[draw_ray]\trx | ry : %d | %d\n", x, y); // ? testing
		// fprintf(stderr, "[draw_ray]\tx1 | y1: %f | %f\n", x1, y1); // ? testing
		if (!check_put_pixel(data, x1, y1))
			return (false);
		mlx_put_pixel(data->graphics->img, x1, y1, RED);
		i++;
	}
	return (true);
}

/**
 * radian = degree * M_PI / 180.0
 */
bool	ray_caster(t_general_data *data)
{
	int		i;
	float	angle;
	t_ray	**raymond;
	t_textures	*textures;

	i = 0;
	raymond = data->graphics->ray;
	textures = data->graphics->textures;
	angle = data->file_data->player->angle + (NB_RAYS * DR); // ! (NB_RAYS * DR) is the FOV angle in radian
	// log_val(data, "ray_caster", 'A'); // ? testing
	// fprintf(stderr, "ray angle: %f\n", angle); // ? testing
	// log_val(data, "ray_caster", 'A'); // ? testing
	// fprintf(stderr, "ray angle: %f\n", angle); // ? testing
	while (i < NB_RAYS)
	{
		if (angle > 2 * M_PI)
			angle -= RESET_ANGLE;
		if (angle < 0)
			angle += RESET_ANGLE;
		textures->hmt = 0;
		textures->vmt = 0;
		if (i == 15){
			vertical_ray(data, raymond[i], angle, textures);
			horizontal_ray(data, raymond[i], angle, textures);
			if (!draw_ray(data, raymond[i]->angle, raymond[i]->x, raymond[i]->y))
				return (error_msg("draw_ray"));

			/**
			 * ! the "3D" window size will be 320/160
			*/
			if (!draw_3d_walls(data, raymond[i], i, textures))
			// if (!draw_3d_map(data, raymond[i], i, textures))
				return (error_msg("draw_3d"));
		}
		// fprintf(stderr, "[ray_caster] dist_v | dist_h : \t%f | %f\n", raymond[i]->dist_v, raymond[i]->dist_h); // ? testing

		// fprintf(stderr, "[ray_caster] rx | ry : \t%f | %f\n", raymond[i]->x, raymond[i]->y); // ? testing

		angle -= (DR * 2); // ! when drawing multiple rays, we need to decrement the angle of each ray
		i++;
	}
	return (true);
}
