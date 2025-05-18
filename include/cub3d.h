
#ifndef CUB3D_H
# define CUB3D_H

/*
	Libraries
*/

# include "../srcs/MLX/mlx.h"
# include "../srcs/LIBFT/libft.h"
# include <stdio.h>
# include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

/*
	Defines
*/

# define WALL				'1'
# define FLOOR				'0'
# define NO 				'NO'
# define SO 				'SO'
# define WE 				'WE'
# define EA 				'EA'
# define C					'C'
# define F					'F'
# define EF					EXIT_FAILURE
# define ES					EXIT_SUCCESS

/*
	Structs
*/

# define S_W 1800 // screen  width
# define S_H 1000 // Screen height
# define FOV 60 //FOV

# define NORTH 2
# define SOUTH 3
# define EAST 4
# define WEST 5


// Colors
# define C_FLOOR 0x1A9D0D
# define C_CEILING 0x335DFF

typedef struct s_line
{
	int x;
	int y;
	int y0;
	int y1;
} t_line;

// Variables with player
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		player_flag;
	int		orientation;
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
	double wall_dst;
	int step_x;
	int step_y;
	int map_x;
	int map_y;
	int line_height;
	int draw_s;
	int draw_e;
	int side;
	int hit;
} t_ray;

typedef struct s_textures
{
	unsigned int	door[64][64];
	unsigned int	east[64][64];
	unsigned int	north[64][64];
	unsigned int	south[64][64];
	unsigned int	west[64][64];
	unsigned int	ceiling;
	unsigned int	floor;
} t_textures;

// Main struct
typedef struct s_data
{
	char **map;
	int		map_height;
	int		map_width;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_player	*plr;
	t_ray		*ray;
	t_line		*line;
	t_textures	textures;
} t_data;

/*
	Func Prototypes
*/
int	free_darray(char **darray);
int	use_atoi(t_data *data, char **colors, char texture);
char	**color_split(char *s);
int	texture_n_colors(t_data *cub3d, char **f_data);
int	ft_strcmp(const char *s1, const char *s2);
void	ft_revtrim(char *s1, char const *set);
char	**extract_f(const char *file_path);
int	validate_content(char **f_data);
int	count_chars(const char *str, char ch);
int	parse_map(t_data *cub3d, char **data, int i);
int	check_walls(t_data *cub3d);
int	find_start(char **f_data);


void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

int rendering(void *param);
void raycast(t_data *data, t_ray *ray);
void paint(t_data *data, t_ray *ray, t_player *player, t_line *line);
void height_Scale(t_ray *ray, t_player *player);
void the_DDA(t_data *data, t_ray *ray);
void getWallSide(t_ray *ray);
void check_steps(t_ray *ray, t_player *player);
void init_ray(t_ray *ray, t_player *player);

void init(t_data *data);
void game_start(t_data *data);


#endif