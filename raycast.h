#ifndef RAYCAST_H
# define RAYCAST_H

#include "MLX/mlx.h"
#include <math.h>
#include <stdio.h>

# define S_W 2000 // screen  width
# define S_H 1000 // Screen height
# define FOV 60 //FOV

typedef struct s_player
{

} t_player;

typedef struct s_raycast
{

} t_raycast;

typedef struct s_data
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	
} t_data;

#endif