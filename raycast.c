#include "raycast.h"

void init_ray(t_ray *ray, t_player *player)
{
	ray->cam_x = (2 * ray->pxl_x) / (double) S_W - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->cam_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->cam_x;
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
	ray->map_x = (int) player->pos_x;
	ray->map_y = (int) player->pos_y;
	ray->hit = 0;
}

void check_steps(t_ray *ray, t_player *player) //(origin point 0,0 is top left corner)
{
	if (ray->dir_x > 0) //move right
	{
		ray->step_x = 1;
		ray->sidedst_x = (ray->map_x + 1.0 - player->pos_x);
	}
	else //move left
	{
		ray->step_x = -1;
		ray->sidedst_x = (player->pos_x - ray->map_x);
	}
	if (ray->dir_y < 0) //move up
	{
		ray->step_y = -1;
		ray->sidedst_y = (player->pos_y - ray->map_y);
	}
	else //move down
	{
		ray->step_y = 1;
		ray->sidedst_y = (ray->map_y + 1.0 - player->pos_y);
	}
}

int rendering(void *param)
{
	t_data *data;
	t_ray *ray;

	data = (t_data *) param;
	ray = malloc(sizeof(t_ray));
	if (!ray)
	{
		printf("malloc error ray\n");
		return (1);
	}
	memset(ray, 0, sizeof(t_ray)); //temp function
	ray->pxl_x = 0;
	while (ray->pxl_x < S_W - 1) //loops over every pixel in width
	{
		raycast(data, ray);
		my_mlx_pixel_put(data, ray->pxl_x, 100, 0xAF0F0); // just to check
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	free(ray);
	return (0);
}

void raycast(t_data *data, t_ray *ray)
{
	t_player *player;

	player = data->plr;
	init_ray(ray, player);
	check_steps(ray, player);
	the_DDA(ray);

	ray->pxl_x++;
}