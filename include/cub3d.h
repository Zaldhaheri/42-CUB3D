#ifndef CUB3D_H
# define CUB3D_H

/*
	Libraries
*/

# include "../srcs/MLX/mlx.h"
# include "../srcs/LIBFT/libft.h"
# include <stdio.h>
# include <fcntl.h>

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
typedef enum keys
{
	UP = 126,
	DOWN = 125,
	RIGHT = 124,
	LEFT = 123,
	W = 13,
	A= 0,
	S = 1,
	D = 2,
	ESC = 53
}	t_keys;

typedef struct s_parsemap
{
	int		fd;
	int		rows;
	int		collumns;
	int		empty_line;
	char	*line;
	char	**map_main;
	char	**map_copy;
	int		player;
	int		x;
	int		y;
}	t_parsemap;

/*
	Func Prototypes
*/
int parse_cub(const char *path, t_parsemap *game);


#endif