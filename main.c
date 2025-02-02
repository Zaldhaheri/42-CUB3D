#include "raycast.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

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

// void draw_box(t_data *data, int x_start, int y_start, int width, int height, int color)
// {
//     for (int y = y_start; y < y_start + height; y++)
//     {
//         for (int x = x_start; x < x_start + width; x++)
//         {
//             my_mlx_pixel_put(data, x, y, color);
//         }
//     }
// }

// void draw_circle(t_data *data, int xc, int yc, int radius, int color)
// {
//     for (int y = yc - radius; y <= yc + radius; y++)
//     {
//         for (int x = xc - radius; x <= xc + radius; x++)
//         {
//             if ((x - xc) * (x - xc) + (y - yc) * (y - yc) <= radius * radius) // Circle equation (x - xc)² + (y - yc)² ≤ r²
//             {
//                 my_mlx_pixel_put(data, x, y, color);
//             }
//         }
//     }
// }

// void draw_triangle(t_data *data, int x, int y, int h, int color)
// {
//     for (int y1 = y; y1 < h + y; y1++)
//     {
//         for (int x1 = x; x1 < x + (y1 - y); x1++)
//             my_mlx_pixel_put(data, x1, y1, color);
//     }
// }

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