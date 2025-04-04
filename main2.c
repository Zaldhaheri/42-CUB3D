#include "./include/cub3d.h"

/*
 JUST FOR TESTING
*/



// int worldMap[MAP_HEIGHT][MAP_WIDTH] = {
//     {1,1,1,1,1,1,1,1,1,1},
//     {1,0,0,0,0,0,0,0,0,1},
//     {1,0,1,1,0,0,0,1,0,1},
//     {1,0,1,0,0,0,0,1,0,1},
//     {1,0,1,0,0,0,0,1,0,1},
//     {1,0,1,0,0,0,0,1,0,1},
//     {1,0,0,0,0,1,1,0,0,1},
//     {1,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,1},
//     {1,1,1,1,1,1,1,1,1,1}
// };

// // init to test my raycast (so i dont wait for parsing)
// void init_player(t_data *data)
// {
// 	t_player *player;

// 	data->plr = malloc(sizeof(t_player));
// 	player = data->plr;
// 	player->pos_x = 5.0;
// 	player->pos_y = 5.0; //x y starting positions
// 	player->dir_x = 0;
// 	player->dir_y = 1; //direction of the vector
// 	player->plane_x = 0;
// 	player->plane_y = 0.7; //camera plane
// }

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
		//my_mlx_pixel_put(data, ray->pxl_x, 100, 0xAF0F0); // just to check
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

void paint(t_data *data, t_ray *ray, t_player *player, t_line *line)
{
	(void)player;
	int y;

	y = 0;
	line->x = ray->pxl_x;
	while (y < ray->draw_s)
	{
		my_mlx_pixel_put(data, line->x, y, C_CEILING);
		y++;
	}
	y = ray->draw_s;
	while (y < ray->draw_e)
	{
		my_mlx_pixel_put(data, line->x, y, 0x9E3513);
		y++;
	}
	y = ray->draw_e;
	while(y < S_H)
	{
		my_mlx_pixel_put(data, line->x, y, C_FLOOR);
		y++;
	}
}
