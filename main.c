#include "raycast.h"

/*
 JUST FOR TESTING
*/

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

int worldMap[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,0,0,0,1,0,1},
    {1,0,1,0,0,0,0,1,0,1},
    {1,0,1,0,0,0,0,1,0,1},
    {1,0,1,0,0,0,0,1,0,1},
    {1,0,0,0,0,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

// init to test my raycast (so i dont wait for parsing)
void init_player(t_data *data)
{
	t_player *player;

	data->plr = malloc(sizeof(t_player));
	player = data->plr;
	player->pos_x = 5.0;
	player->pos_y = 5.0;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.6;
}

/*
  END OF TESTING
*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= S_W || y >= S_H)
	{
		printf("pixel out of range!\n");
		return ;
	}
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, S_W, S_H, "CUB3D");
	data->img = mlx_new_image(data->mlx, S_W, S_H);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
}

void init_ray(t_ray *ray, t_player *player)
{
	ray->cam_x = (2 * ray->pxl_x) / (double) S_W - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->cam_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->cam_x;
}

void raycast(t_data *data, t_ray *ray)
{
	t_player *player;

	player = data->plr;
	init_ray(ray, player);

	ray->pxl_x++;
}

int rendering(void *param)
{
	t_data *data;
	t_ray *ray;

	data = (t_data *) param;
	ray = malloc(sizeof(t_ray));
	ray->pxl_x = 0;
	printf("raycast loop!\n");
	while (ray->pxl_x < S_W - 1) //loops over every pixel in width
	{
		raycast(data, ray);
		my_mlx_pixel_put(data, ray->pxl_x, 100, 0xAF0F0); // just to check
	}
	free(ray);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

void game_start(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop_hook(data->mlx, rendering, data);
	mlx_loop(data->mlx);
}

int main()
{
	t_data data;

	init(&data);
	init_player(&data);
	game_start(&data);

	return (0);
}
