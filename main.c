#include "./include/cub3d.h"

// Prototype parsing

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

int worldMap[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},//
    {1,0,0,0,0,0,0,0,0,1},//
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,0,1},
    {1,1,0,0,0,0,0,0,1,1},
    {1,1,1,1,1,1,1,1,1,1}
};
	
// init to test my raycast (so i dont wait for parsing)
void test_init_player(t_data *data)
{
	t_player	*player;

	data->plr = malloc(sizeof(t_player));
	player = data->plr;
	player->pos_x = 5.5;
	player->pos_y = 5.5;
	player->dir_x = -0.5;
	player->dir_y = 0.5;
	update_plane(player);	
}

// void test_init_parsing(t_data *data)
// {
// 	t_parse *parsing;

// 	data->parsing = malloc(sizeof(t_parse));
// 	parsing = data->parsing;
// 	parsing->map = malloc(sizeof(int *) * MAP_HEIGHT);
// 	if (!parsing->map)
// 		exit(1); // or handle error
// 	for (int i = 0; i < MAP_HEIGHT; i++) {
// 		parsing->map[i] = malloc(sizeof(int) * MAP_WIDTH);
// 		if (!parsing->map[i])
//     		exit(1); // or handle error
// 		for (int j = 0; j < MAP_WIDTH; j++) {
//     		parsing->map[i][j] = worldMap[i][j];
// 		}
// 	}
// }

// Parsing test ^

// change this location max

static int	parse(char *path, t_data *data)
{
	char	**content;
	int		index;

	content = extract_f(path);
	if (content == NULL)
		return (printf("Error\nThe file wasn't found.\n"), -1);
	if (validate_content(content) < 0
		|| texture_n_colors(data, content) < 0)
		return (free_darray(content), -1);
	index = find_start(content);
	if (index == -1)
		printf("Error: No valid map found in the file.\n");
	if (index == -1 || parse_map(data, content + index, index) == -1)
		return (free_darray(content), -1);
	free_darray(content);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (printf("Error\nUsage: ./cub3d_parser <path_to_cub_file>\n"), 1);
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		return (printf("Error\nIncorrect file name\n"), 2);
	ft_memset(&data, 0, sizeof(data));
	data.mlx = mlx_init();
	if (!data.mlx)
		return (printf("Error\nMLX failed\n"), -1);
	if (parse(argv[1], &data) == -1)
		return (free(data.mlx), -1);
	// Note: Need to handle broken xpm
	// Note: Don't forget to free the allocated memory for the map and other structures
	// DEBUGGING //
	printf("Parsing done.\n");
	printf("Map:\n");
	for (int i = 0; i < data.map_height; i++)
	{
		for (int j = 0; j < data.map_width; j++)
			printf("%c ", data.map[i][j]);
		printf("\n");
	}
	printf("Textures and colors parsed successfully.\n");
	printf("Player position: (%lf, %lf)\n", data.plr->pos_x, data.plr->pos_y);
	printf("Player direction: (%lf, %lf)\n", data.plr->dir_x, data.plr->dir_y);
	printf("Player plane: (%lf, %lf)\n", data.plr->plane_x, data.plr->plane_y);
	printf("Textures:\n");
    printf("Floor color: 0x%06X\n", data.textures.floor);
    printf("Ceiling color: 0x%06X\n", data.textures.ceiling); 
	printf("Map height: %d\n", data.map_height);
	printf("Map width: %d\n", data.map_width);
	// init(&data);
	// test_init_parsing(&data);
	// test_init_player(&data);
	// game_start(&data);

	// free(data.plr);
	return (0);
}
