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
void	init_map(t_parsemap **map);
void	image_check(void);
void	path_validation(char *path, t_parsemap **map);
void	retrieve_map(char *path, t_parsemap **map);
void	free_maps(char **main_map, char **map_copy, t_parsemap *map);
void	check_map_size(t_parsemap **map);
void	check_map_borders(t_parsemap **map);
int		check_top_bottom(char *row, char target);
void	check_map_elements(t_parsemap **map);
void	check_character(char c, t_parsemap **map);
void	check_element_amount(t_parsemap **map);

#endif