/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:17:07 by zaldhahe          #+#    #+#             */
/*   Updated: 2025/05/20 15:23:48 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	*(unsigned int *) dst = color;
}

void	init(t_data *data)
{
	data->win = mlx_new_window(data->mlx, S_W, S_H, "CUB3D");
	data->img = mlx_new_image(data->mlx, S_W, S_H);
	data->addr = mlx_get_data_addr(data->img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	data->line = malloc(sizeof(t_line));
	if (!data->line)
	{
		printf("malloc error: line\n");
		exit(1);
	}
}

void	update_plane(t_player *plr)
{
	plr->plane_x = -plr->dir_y * FOV;
	plr->plane_y = plr->dir_x * FOV;
}

void	game_start(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, hook_keys, data);
	mlx_hook(data->win, 17, 0, hook_exit, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop_hook(data->mlx, rendering, data);
	mlx_loop(data->mlx);
}

int	rendering(void *param)
{
	t_data	*data;
	t_ray	*ray;

	data = (t_data *) param;
	ray = malloc(sizeof(t_ray));
	if (!ray)
	{
		printf("malloc error ray\n");
		return (1);
	}
	memset(ray, 0, sizeof(t_ray));
	ray->pxl_x = 0;
	while (ray->pxl_x < S_W)
	{
		raycast(data, ray);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	free(ray);
	return (0);
}
