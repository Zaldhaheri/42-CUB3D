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

void normalize(double *x, double *y)
{
	double len = sqrt((*x) * (*x) + (*y) * (*y));
	if (len != 0)
	{
		*x /= len;
		*y /= len;
	}
}

void update_plane(t_player *plr)
{
	plr->plane_x = -plr->dir_y * FOV;
	plr->plane_y = plr->dir_x * FOV;
}

void look_left(t_player *plr)
{
	double old_dir_x;
	double old_plane_x;
	double old_plane_y;

	old_dir_x = plr->dir_x;
	old_plane_x = plr->plane_x;
	old_plane_y = plr->plane_y;
	plr->dir_x = plr->dir_x * cos(-ROT_SPEED) - plr->dir_y * sin(-ROT_SPEED);
	plr->dir_y = old_dir_x * sin(-ROT_SPEED) + plr->dir_y * cos(-ROT_SPEED);
	plr->plane_x = plr->plane_x * cos(-ROT_SPEED) - old_plane_y * sin(-ROT_SPEED);
	plr->plane_y = old_plane_x * sin(-ROT_SPEED) + old_plane_y * cos(-ROT_SPEED);
	normalize(&plr->dir_x, &plr->dir_y);
	normalize(&plr->plane_x, &plr->plane_y);
	update_plane(plr);
}

void look_right(t_player *plr)
{
	double old_dir_x = plr->dir_x;
	double old_plane_x = plr->plane_x;
	double old_plane_y = plr->plane_y;

	plr->dir_x = plr->dir_x * cos(ROT_SPEED) - plr->dir_y * sin(ROT_SPEED);
	plr->dir_y = old_dir_x * sin(ROT_SPEED) + plr->dir_y * cos(ROT_SPEED);
	plr->plane_x = plr->plane_x * cos(ROT_SPEED) - old_plane_y * sin(ROT_SPEED);
	plr->plane_y = old_plane_x * sin(ROT_SPEED) + old_plane_y * cos(ROT_SPEED);
	normalize(&plr->dir_x, &plr->dir_y);
	normalize(&plr->plane_x, &plr->plane_y);
	update_plane(plr);
}

void move_forward(t_data *data, t_player *plr)
{
	int pos_x;
	int pos_y;

	pos_x = (int) plr->pos_x + plr->dir_x * MOVE_SPEED;
	pos_y = (int) plr->pos_y + plr->dir_y * MOVE_SPEED;
	if (data->parsing->map[pos_y][pos_x] == 0)
	{
		plr->pos_x += plr->dir_x * MOVE_SPEED;
		plr->pos_y += plr->dir_y * MOVE_SPEED;
	}
}

void move_backward(t_player *plr)
{
	plr->pos_x -= plr->dir_x * MOVE_SPEED;
	plr->pos_y -= plr->dir_y * MOVE_SPEED;
}

void move_left(t_player *plr)
{
	plr->pos_x -= plr->plane_x * MOVE_SPEED;
	plr->pos_y -= plr->plane_y * MOVE_SPEED;
}

void move_right(t_player *plr)
{
	plr->pos_x += plr->plane_x * MOVE_SPEED;
	plr->pos_y += plr->plane_y * MOVE_SPEED;
}

int hook_keys(int key, t_data *data)
{
	if (key == 53)
	{
		printf("ESC, Exiting\n");
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	else if (key == 123) //<-
	{
		printf("look left\n");
		look_left(data->plr);
	}
	else if (key == 124) //->
	{
		printf("look right\n");
		look_right(data->plr);
	}
	else if (key == 13) //W
	{
		printf("move forward\n");
		move_forward(data, data->plr);
	}
	else if (key == 0) //A
	{
		printf("move left\n");
		move_left(data->plr);
	}
	else if (key == 1) //S
	{
		printf("move backward\n");
		move_backward(data->plr);
	}
	else if (key == 2) //D
	{
		printf("move right\n");
		move_right(data->plr);
	}
	else
		printf("key: %d\n", key);
	return (0);
}

int hook_exit(t_data *data)
{
	printf("Window exit\n");
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

void game_start(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, hook_keys, data);
	mlx_hook(data->win, 17, 0, hook_exit, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop_hook(data->mlx, rendering, data);
	mlx_loop(data->mlx);
}

// Runs on the loop hook, casts the rays and puts image to window
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
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	free(ray);
	return (0);
}

// runs the game

