
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

# define S_W 1800 // screen  width
# define S_H 1000 // Screen height
# define FOV 0.60 //FOV
# define NORTH 2
# define SOUTH 3
# define EAST 4
# define WEST 5
# define C_FLOOR 0x1A9D0D
# define C_CEILING 0x335DFF

#define ROT_SPEED 0.05

/*
	Structs
*/

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

typedef struct s_parse 
{
	unsigned int	no[64][64];
	unsigned int	so[64][64];
	unsigned int	we[64][64];
	unsigned int	ea[64][64];
	int		f;
	int		c;
	int	**map;
	int		map_height;
	int		map_width;
} t_parse;

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
	t_line		*line;
	t_parse		*parsing;
} t_data;

/*
	Func Prototypes
*/
int		check_content(char **content);
int 	color_and_texture(t_data *game, char **content);
int		parse_map(t_data *game, char **content, int start);

int		free_darray(char **darray);
void	trim_end(char *string, char *set);
int		string_compare(const char *string1, const char *string2);
char	**split_color_channels(char *line);
int		atoi_colors(t_data *game, char **colors, char texture);
int		check_for_map(char **file_data);
void	reverse_map(char **map);
char	**extract_content(char *path);
int		count_color_channels(char *line);
int		string_compare(const char *string1, const char *string2);
int		check_indents(int *identifier_count);
int	setting_color(t_data *data, char *line);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

void update_plane(t_player *plr);

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