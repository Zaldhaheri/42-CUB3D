#include "./include/cub3d.h"

// Prototype parsing

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

int worldMap[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},//
    {1,0,0,0,0,0,0,0,0,1},//
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,0,0,0,0,0,0,1,1},
    {1,1,1,1,1,1,1,1,1,1}
};
	
// init to test my raycast (so i dont wait for parsing)
void test_init_player(t_data *data)
{
	t_player	*player;

	data->plr = malloc(sizeof(t_player));
	player = data->plr;
	player->pos_x = 5.0;
	player->pos_y = 5.0;
	player->dir_x = -0.5;
	player->dir_y = 0.5;
	update_plane(player);	
}

void test_init_parsing(t_data *data)
{
	t_parse *parsing;

	data->parsing = malloc(sizeof(t_parse));
	parsing = data->parsing;
	parsing->map = malloc(sizeof(int *) * MAP_HEIGHT);
	if (!parsing->map)
		exit(1); // or handle error
	for (int i = 0; i < MAP_HEIGHT; i++) {
		parsing->map[i] = malloc(sizeof(int) * MAP_WIDTH);
		if (!parsing->map[i])
    		exit(1); // or handle error
		for (int j = 0; j < MAP_WIDTH; j++) {
    		parsing->map[i][j] = worldMap[i][j];
		}
	}
}

// Parsing test ^

// change this location max
int	parse_cub(char *path, t_data *data)
{
	char	**content;
	int		index;

	content = extract_content(path);
	if (!content)
		return (write(1, "Error\nInvalid file\n", 20), 0);
	if (!check_content(content) || !color_and_texture(data, content))
		return (free_darray(content), 0);
	index = check_for_map(content);
	if (!index || !parse_map(data, content + index, index))
		return (free_darray(content), 0);
	free_darray(content);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	(void) argc;
	(void) argv;

	// if (argc != 2)
	// 	write(1, "Error\nUsage: ./cub3d <path_to_cub_file>\n", 35), exit(EF);
	// if (ft_strnstr(argv[1], ".cub", 5))
	// 	write(1, "Error\nInvalid file extension\n", 30), exit(EF);
	// ft_memset(&data, 0, sizeof(t_data));
	// if (!parse_cub(argv[1], &data))
	// 	free(&data),write(1, "Error\nParsing failed\n", 22), exit(EF);
	init(&data);
	test_init_parsing(&data);
	test_init_player(&data);
	game_start(&data);

	//free(data.plr);
	return (0);
}
