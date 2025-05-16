#include "./include/cub3d.h"

// Calculates the height scale of the wall based on the distance from the player and plane
void height_Scale(t_ray *ray)
{
	ray->line_height = S_H / ray->wall_dst;
	ray->draw_s = -ray->line_height / 2 + (S_H / 2);
	if (ray->draw_s <= 0)
		ray->draw_s = 0;
	ray->draw_e = ray->line_height / 2 + (S_H / 2);
	if (ray->draw_e >= S_W)
		ray->draw_e = S_W - 1;
}


// Colors in the ceiling, wall and, floor pixel by pixel based on calculations from height scale
void paint(t_data *data, t_ray *ray, t_player *player, t_line *line)
{
	(void)player;
	int y;

	y = 0;
	line->x = ray->pxl_x;
	while (y < ray->draw_s) //draw ceiling
	{
		my_mlx_pixel_put(data, line->x, y, C_CEILING);
		y++;
	}
	y = ray->draw_s;
	int wall_color = 0xA45670;
	if (ray->side == NORTH)
		wall_color = 0xFF0000; // red
	else if (ray->side == SOUTH)
		wall_color = 0x00FF00; // green
	else if (ray->side == EAST)
		wall_color = 0x0000FF; // blue
	else if (ray->side == WEST)
		wall_color = 0xFFFF00; // yellow
	while (y < ray->draw_e)
	{
		my_mlx_pixel_put(data, line->x, y, wall_color);
		y++;
	}
	y = ray->draw_e;
	while(y < S_H) //draw floor
	{
		my_mlx_pixel_put(data, line->x, y, C_FLOOR);
		y++;
	}
}
