#include "raycast.h"

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

void set_FC(t_data *data)
{
	int y;
	int	x;

	y = 0;
	while (y < S_H)
	{
		x = 0;
		while (x < S_W)
		{
			if (y < S_H / 2)
				my_mlx_pixel_put(data, x, y, C_CEILING);
			else
				my_mlx_pixel_put(data, x, y, C_FLOOR);
			x++;
		}
		y++;
	}
}

int main()
{
	t_data data;

	init(&data);
	set_FC(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
