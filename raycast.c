#include "./include/cub3d.h"

void init_ray(t_ray *ray, t_player *player)
{
	ray->cam_x = (2 * ray->pxl_x) / (double) S_W - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->cam_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->cam_x;
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
	ray->map_x = (int) player->pos_x;
	ray->map_y = (int) player->pos_y;
	ray->hit = 0;
}

void check_steps(t_ray *ray, t_player *player) //(origin point 0,0 is top left corner)
{
	if (ray->dir_x >= 0) //move right
	{
		ray->step_x = 1;
		ray->sidedst_x = (ray->map_x + 1.0 - player->pos_x);
	}
	else //move left
	{
		ray->step_x = -1;
		ray->sidedst_x = (player->pos_x - ray->map_x);
	}
	if (ray->dir_y < 0) //move up
	{
		ray->step_y = -1;
		ray->sidedst_y = (player->pos_y - ray->map_y);
	}
	else //move down
	{
		ray->step_y = 1;
		ray->sidedst_y = (ray->map_y + 1.0 - player->pos_y);
	}
}

void getWallSide(t_ray *ray)
{
	if (ray->sidedst_x < ray->sidedst_y)
	{
		ray->sidedst_x += ray->delta_x;
		ray->map_x += ray->step_x;
		if (ray->step_x == -1)
			ray->side = EAST;
		else
			ray->side = WEST;
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

void the_DDA(t_data *data, t_ray *ray)
{
	while(!ray->hit)
	{
		getWallSide(ray);
		if (data->parsing->map[ray->map_y][ray->map_x] == 1)
			ray->hit = 1;
	}
}

void height_Scale(t_ray *ray, t_player *player)
{
	if (ray->side == EAST || ray->side == WEST)
		ray->wall_dst = ((double) ray->map_x - player->pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->wall_dst = ((double) ray->map_y - player->pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
	ray->line_height = S_H / ray->wall_dst;
	ray->draw_s = -ray->line_height / 2 + ((S_H / 2) * player->plane_y);
	if (ray->draw_s <= 0)
		ray->draw_s = 0;
	ray->draw_e = ray->line_height / 2 + ((S_H / 2) * player->plane_y);
	if (ray->draw_e >= S_W)
		ray->draw_e = S_W - 1;
}

void raycast(t_data *data, t_ray *ray)
{
	t_player *player;
	t_line	*line;

	player = data->plr;
	line = data->line;
	init_ray(ray, player);
	check_steps(ray, player);
	the_DDA(data, ray);
	height_Scale(ray, player);
	paint(data, ray, player, line);
	
	ray->pxl_x++;
}