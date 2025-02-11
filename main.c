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
	player->pos_y = 5.0; //x y starting positions
	player->dir_x = -1;
	player->dir_y = 0; //direction of the vector
	player->plane_x = 0;
	player->plane_y = 0.6; //camera plane
}

/*
  END OF TESTING
*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > S_W || y > S_H)
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

void the_DDA(t_ray *ray)
{
	while (ray->hit == 0)
	{
		//check which side is closer, vertical(x) or horizontal(y) and do the thing
		if (ray->sidedst_x < ray->sidedst_y)
		{
			ray->sidedst_x += ray->delta_x;
			ray->map_x += ray->step_x;
			if (ray->step_x == -1)
				ray->side = EAST;
			else
				ray->side = WEST;
		}
		else
		{
			ray->sidedst_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // 1 meaning horizontal wall
			if (ray->step_y == -1)
				ray->side = NORTH;
			else
				ray->side = SOUTH;
		}
		if (worldMap[ray->map_y][ray->map_x] > 0)
			ray->hit = 1;
	}
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

	free(data.plr);
	return (0);
}
