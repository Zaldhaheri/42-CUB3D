#include "./include/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= S_W || y >= S_H)
	{
		printf("pixel out of bounds: (%d, %d)\n", x, y);
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

	data->line = malloc(sizeof(t_line));
	if (!data->line)
	{
		printf("malloc error: line\n");
		exit(1);
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
	while (ray->pxl_x < S_W) //loops over every pixel in width
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

	if (ray->draw_s < 0)
		ray->draw_s = 0;
	if (ray->draw_e >= S_H)
		ray->draw_e = S_H - 1;

	while (y < ray->draw_s) //draw ceiling
	{
		my_mlx_pixel_put(data, line->x, y, C_CEILING);
		y++;
	}
	y = ray->draw_s;
	while (y < ray->draw_e) //draw wall
	{
		my_mlx_pixel_put(data, line->x, y, 0x9E3513);
		y++;
	}
	y = ray->draw_e;
	while(y < S_H) //draw floor
	{
		my_mlx_pixel_put(data, line->x, y, C_FLOOR);
		y++;
	}
}
