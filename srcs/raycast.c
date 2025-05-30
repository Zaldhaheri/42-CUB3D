/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:32:51 by zaldhahe          #+#    #+#             */
/*   Updated: 2025/05/20 19:27:13 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_ray(t_ray *ray, t_player *player)
{
	ray->cam_x = (2 * (ray->pxl_x + 0.5)) / (double) S_W - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->cam_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->cam_x;
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
	ray->map_x = (int) player->pos_x;
	ray->map_y = (int) player->pos_y;
	ray->hit = 0;
}

void	check_steps(t_ray *ray, t_player *player)
{
	if (ray->dir_x >= 0)
	{
		ray->step_x = 1;
		ray->sidedst_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = -1;
		ray->sidedst_x = (player->pos_x - ray->map_x) * ray->delta_x;
	}
	if (ray->dir_y >= 0)
	{
		ray->step_y = 1;
		ray->sidedst_y = (player->pos_y - ray->map_y) * ray->delta_y;
		ray->sidedst_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = -1;
		ray->sidedst_y = (player->pos_y - ray->map_y) * ray->delta_y;
	}
}

void	get_wall_side(t_ray *ray)
{
	if (ray->sidedst_x <= ray->sidedst_y)
	{
		ray->sidedst_x += ray->delta_x;
		ray->map_x += ray->step_x;
		if (ray->step_x == -1)
			ray->side = WEST;
		else
			ray->side = EAST;
	}
	else
	{
		ray->sidedst_y += ray->delta_y;
		ray->map_y += ray->step_y;
		if (ray->step_y == -1)
			ray->side = SOUTH;
		else
			ray->side = NORTH;
	}
}

void	dda(t_data *data, t_ray *ray)
{
	while (!ray->hit)
	{
		get_wall_side(ray);
		if (data->map[ray->map_y][ray->map_x] == '1')
		{
			ray->hit = 1;
			if (ray->side == EAST || ray->side == WEST)
				ray->wall_dst = (ray->map_x - data->plr->pos_x
						+ (1 - ray->step_x) / 2.0) / ray->dir_x;
			else
				ray->wall_dst = (ray->map_y - data->plr->pos_y
						+ (1 - ray->step_y) / 2.0) / ray->dir_y;
		}
	}
}

void	raycast(t_data *data, t_ray *ray)
{
	t_player	*player;
	t_line		*line;

	player = data->plr;
	line = data->line;
	init_ray(ray, player);
	check_steps(ray, player);
	dda(data, ray);
	height_scale(ray);
	paint(data, ray, line);
	ray->pxl_x++;
}
