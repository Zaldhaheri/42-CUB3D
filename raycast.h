#ifndef RAYCAST_H
# define RAYCAST_H

#include "MLX/mlx.h"
#include <math.h>
#include <stdio.h>

# define S_W 2000 // screen  width
# define S_H 1000 // Screen height
# define FOV 60 // FOV

// Colors
# define C_FLOOR 0x1A9D0D
# define C_CEILING 0x335DFF

// Variables with player
typedef struct s_player
{
	int plr_pxl_x;
	int plr_pxl_y;
	
} t_player;

// Variables with rays
typedef struct s_ray
{
	double ray_distance;
	double ray_angle;
	int flag;
} t_ray;

// Variables with maps (max)
typedef struct s_map
{
	char **map_arr;
	int map_w;
	int map_h;
} t_map;

// Main struct
typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_player	*plr;
	t_ray		*ray;
	t_map		*map;
} t_data;

#endif