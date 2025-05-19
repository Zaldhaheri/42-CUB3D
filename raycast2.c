#include "./include/cub3d.h"

// Calculates the height scale of the wall based on the distance from the player and plane
void height_Scale(t_ray *ray)
{
	ray->line_height = S_H / ray->wall_dst;
	ray->draw_s = -ray->line_height / 2 + (S_H / 2);
	if (ray->draw_s < 0)
		ray->draw_s = 0;
	ray->draw_e = ray->line_height / 2 + (S_H / 2);
	if (ray->draw_e >= S_H)
		ray->draw_e = S_H - 1;
}


// Colors in the ceiling, wall and, floor pixel by pixel based on calculations from height scale
void paint(t_data *data, t_ray *ray, t_player *player, t_line *line)
{
	(void)player;
	int y;
	unsigned int (*tex)[64];
	double wall_x;
	int tex_x;
	int d;
	int tex_y;
	unsigned int color;

	y = 0;
	line->x = ray->pxl_x;
	while (y < ray->draw_s) //draw ceiling
	{
		my_mlx_pixel_put(data, line->x, y, data->textures.ceiling);
		y++;
	}
	if (ray->side == NORTH)
		tex = data->textures.north;	
	else if (ray->side == SOUTH)
		tex = data->textures.south;
	else if (ray->side == EAST)
		tex = data->textures.east;
	else if (ray->side == WEST)
		tex = data->textures.west;

	if (ray->side == EAST || ray->side == WEST)
		wall_x = data->plr->pos_y + ray->wall_dst * ray->dir_y;
	else
		wall_x = data->plr->pos_x + ray->wall_dst * ray->dir_x;
	wall_x -= (int) wall_x;
	tex_x = (int) (wall_x * 64);
	if (ray->side == EAST || ray->side == SOUTH)
		tex_x = 64 - tex_x - 1;
	y = ray->draw_s;
	while (y < ray->draw_e)
	{
		d = y * 256 - S_H * 128 + ray->line_height * 128;
		tex_y = ((d * 64) / ray->line_height) / 256;
		color = tex[tex_y][tex_x];
		my_mlx_pixel_put(data, line->x, y, color);
		y++;
	}
	y = ray->draw_e;
	while(y < S_H) //draw floor
	{
		my_mlx_pixel_put(data, line->x, y, data->textures.floor);
		y++;
	}
}
