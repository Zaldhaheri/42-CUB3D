/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:39:31 by zaldhahe          #+#    #+#             */
/*   Updated: 2025/05/20 16:52:01 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void	height_scale(t_ray *ray)
{
	if (ray->wall_dst < 0.0001)
		ray->wall_dst = 0.0001;
	ray->line_height = (int)(S_H / ray->wall_dst);
	ray->draw_s = -ray->line_height / 2 + (S_H / 2);
	if (ray->draw_s < 0)
		ray->draw_s = 0;
	ray->draw_e = ray->line_height / 2 + (S_H / 2);
	if (ray->draw_e >= S_H)
		ray->draw_e = S_H - 1;
}

void	paint(t_data *data, t_ray *ray, t_line *line)
{
	int				y;

	y = 0;
	line->x = ray->pxl_x;
	while (y < ray->draw_s)
	{
		my_mlx_pixel_put(data, line->x, y, data->textures.ceiling);
		y++;
	}
	paint_wall(data, ray, line);
	y = ray->draw_e;
	while (y < S_H)
	{
		my_mlx_pixel_put(data, line->x, y, data->textures.floor);
		y++;
	}
}

void	paint_wall(t_data *data, t_ray *ray, t_line *line)
{
	double			wall_x;
	int				tex_x;

	if (ray->side == NORTH)
		data->tex = data->textures.north;
	else if (ray->side == SOUTH)
		data->tex = data->textures.south;
	else if (ray->side == EAST)
		data->tex = data->textures.east;
	else if (ray->side == WEST)
		data->tex = data->textures.west;
	if (ray->side == NORTH || ray->side == SOUTH)
		wall_x = data->plr->pos_x + ray->wall_dst * ray->dir_x;
	else
		wall_x = data->plr->pos_y + ray->wall_dst * ray->dir_y;
	wall_x -= (int) wall_x;
	tex_x = (int)(wall_x * TEX_SIZE);
	if (ray->side == EAST || ray->side == SOUTH)
		tex_x = TEX_SIZE - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= TEX_SIZE)
		tex_x = TEX_SIZE - 1;
	paint_wall2(data, ray, line, tex_x);
}

void	paint_wall2(t_data *data, t_ray *ray, t_line *line, int tex_x)
{
	unsigned int	color;
	int				d;
	int				tex_y;
	int				y;

	y = ray->draw_s;
	while (y < ray->draw_e)
	{
		d = y * 256 - S_H * 128 + ray->line_height * 128;
		tex_y = ((d * TEX_SIZE) / ray->line_height) / 256;
		color = data->tex[TEX_SIZE - 1 - tex_x][tex_y];
		my_mlx_pixel_put(data, line->x, y, color);
		y++;
	}
}
