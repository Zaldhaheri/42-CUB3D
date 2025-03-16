#include "./include/cub3d.h"

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
	printf("i am here?");
	t_data	data;

	if (argc != 2)
		(write(1, "Error\nUsage: ./cub3d <path_to_cub_file>\n", 35), exit(EF));
	printf("here?");
	if (ft_strnstr(argv[1], ".cub", 5))
		(write(1, "Error\nInvalid file extension\n", 30), exit(EF));
	ft_memset(&data, 0, sizeof(t_data));
	if (!parse_cub(argv[1], &data))
		(free(&data),write(1, "Error\nParsing failed\n", 22), exit(EF));

	init(&data);
	//init_player(&data);
	game_start(&data);

	free(data.plr);
	return (0);
}
