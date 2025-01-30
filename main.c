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

void draw_box(t_data *data, int x_start, int y_start, int width, int height, int color)
{
    for (int y = y_start; y < y_start + height; y++)
    {
        for (int x = x_start; x < x_start + width; x++)
        {
            my_mlx_pixel_put(data, x, y, color);
        }
    }
}

int main()
{
    t_data data;

    init(&data);
    
    // draw_box(&data, 0, 0, S_W, S_H, 0x00FF0000); // Draw a red box at (100,100) with width 200, height 150
    // draw_box(&data, 0, S_H/2, S_W, S_H/2, 0xAE); // Draw a red box at (100,100) with width 200, height 150

    draw_box(&data, 0, 0, S_W, S_H, 0x732F);
    draw_box(&data, 0, S_H / 3, S_W, (2 * S_H) / 3, 0xFFFFFF);
    draw_box(&data, 0, (2 * S_H) / 3, S_W, S_H / 3 + 1, 0x0);
    draw_box(&data, 0, 0, S_W / 4, S_H, 0x00FF0000);

    // draw_box(&data, 0, 0, S_W, S_H, 0xFFFFFF);
    // draw_box(&data, 0, S_H / 3, S_W, (2 * S_H) / 3, 0x33A0);
    // draw_box(&data, 0, (2 * S_H) / 3, S_W, S_H / 3 + 1, 0xDA291C);

    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    mlx_loop(data.mlx);
    return (0);
}


// int main()
// {
//     t_data data;

//     init(&data);
    
//     while ()
//     my_mlx_pixel_put(&data, 5, 5, 0x00FF0000);
//     mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
//     mlx_loop(data.mlx);
//     return (0);
// }