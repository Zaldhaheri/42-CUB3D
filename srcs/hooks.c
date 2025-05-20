/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:17:48 by zaldhahe          #+#    #+#             */
/*   Updated: 2025/05/20 19:27:09 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	normalize(double *x, double *y)
{
	double	len;

	len = sqrt((*x) * (*x) + (*y) * (*y));
	if (len != 0)
	{
		*x /= len;
		*y /= len;
	}
}

void	look_left(t_player *plr)
{
	double	old_dir_x;
	double	old_plane_x;
	double	old_plane_y;

	old_dir_x = plr->dir_x;
	old_plane_x = plr->plane_x;
	old_plane_y = plr->plane_y;
	plr->dir_x = plr->dir_x * cos(-ROT_SPEED) - plr->dir_y * sin(-ROT_SPEED);
	plr->dir_y = old_dir_x * sin(-ROT_SPEED) + plr->dir_y * cos(-ROT_SPEED);
	plr->plane_x = plr->plane_x * cos(-ROT_SPEED) - old_plane_y
		* sin(-ROT_SPEED);
	plr->plane_y = old_plane_x * sin(-ROT_SPEED) + old_plane_y
		* cos(-ROT_SPEED);
	normalize(&plr->dir_x, &plr->dir_y);
	normalize(&plr->plane_x, &plr->plane_y);
	update_plane(plr);
}

void	look_right(t_player *plr)
{
	double	old_dir_x;
	double	old_plane_x;
	double	old_plane_y;

	old_dir_x = plr->dir_x;
	old_plane_x = plr->plane_x;
	old_plane_y = plr->plane_y;
	plr->dir_x = plr->dir_x * cos(ROT_SPEED) - plr->dir_y * sin(ROT_SPEED);
	plr->dir_y = old_dir_x * sin(ROT_SPEED) + plr->dir_y * cos(ROT_SPEED);
	plr->plane_x = plr->plane_x * cos(ROT_SPEED) - old_plane_y * sin(ROT_SPEED);
	plr->plane_y = old_plane_x * sin(ROT_SPEED) + old_plane_y * cos(ROT_SPEED);
	normalize(&plr->dir_x, &plr->dir_y);
	normalize(&plr->plane_x, &plr->plane_y);
	update_plane(plr);
}

int	hook_exit(t_data *data)
{
	printf("Window exit\n");
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

int	hook_keys(int key, t_data *data)
{
	if (key == 53)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	else if (key == 123)
		look_left(data->plr);
	else if (key == 124)
		look_right(data->plr);
	else if (key == 13 || key == 126)
		move_forward(data, data->plr);
	else if (key == 0)
		move_left(data, data->plr);
	else if (key == 1 || key == 125)
		move_backward(data, data->plr);
	else if (key == 2)
		move_right(data, data->plr);
	else
		printf("%d\n", key);
	return (0);
}
