#ifndef RAYCAST_H
# define RAYCAST_H

#include "MLX/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

# define S_W 1800 // screen  width
# define S_H 1000 // Screen height
# define FOV 60 // FOV

# define NORTH 2
# define SOUTH 3
# define EAST 4
# define WEST 5


// Colors
# define C_FLOOR 0x1A9D0D
# define C_CEILING 0x335DFF

// Variables with player
typedef struct s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
} t_player;

// Variables with rays
typedef struct s_ray
{
	int pxl_x;
	double dir_x;
	double dir_y;
	double delta_x;
	double delta_y;
	double sidedst_x;
	double sidedst_y;
	double cam_x;
	int step_x;
	int step_y;
	int map_x;
	int map_y;
	int side;
	int hit;
} t_ray;

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
} t_data;

void raycast(t_data *data, t_ray *ray);
int rendering(void *param);
void check_steps(t_ray *ray, t_player *player);
void init_ray(t_ray *ray, t_player *player);

#endif