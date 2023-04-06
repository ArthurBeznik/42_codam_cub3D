#include <graphics.h>

bool init_rays(t_general_data *data)
{
	int		i;
	t_ray	**ray;

	i = 0;
	ray = (t_ray **)malloc(sizeof(t_ray) * NB_RAYS);
	if (!ray)
		return (error_msg("Malloc ray struct"));
	while (i < NB_RAYS)
	{
		ray[i] = (t_ray *)malloc(sizeof(t_ray));
		if (!ray)
			// ! free ray
			return (error_msg("Malloc ray ptr"));
		ray[i]->x = 999;
		ray[i]->y = 999;
		ray[i]->angle = 999;
		ray[i]->off_x = 999;
		ray[i]->off_y = 999;
		ray[i]->hit_x = 999;
		ray[i]->hit_y = 999;
		ray[i]->vx = 999;
		ray[i]->vy = 999;
		ray[i]->dist_v = 999;
		ray[i]->dist_h = 999;
		ray[i]->tan_var = 999;
		ray[i]->dof = 999;
		i++;
	}
	data->graphics->ray = ray;
	return (true);
}

bool	init_graphics(t_general_data *data, t_graphics *graphics)
{
	graphics->width = data->file_data->map_data->col * PIXELS;
	graphics->height = (data->file_data->map_data->row * PIXELS) + PIXELS;

	graphics->mlx = mlx_init(graphics->width * 2, graphics->height, "cub3D", true);
	// graphics->mlx = NULL; // ? testing
	if (!graphics->mlx)
		return (error_msg("mlx_init"));

	graphics->img = mlx_new_image(graphics->mlx, graphics->width, graphics->height);
	// graphics->img = NULL; // ? testing
	if (!graphics->img)
	{
		mlx_terminate(graphics->mlx);
		return (error_msg("mlx_new_image"));
	}

	graphics->img_3d = mlx_new_image(graphics->mlx, 500, 500);
	if (!graphics->img_3d)
	{
		mlx_terminate(graphics->mlx);
		return (error_msg("mlx_new_image 3D"));
	}
	return (true);
}
