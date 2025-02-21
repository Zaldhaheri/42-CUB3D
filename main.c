#include "./include/cub3d.h"

int	parse_cub(const char *path, t_data *game)
{
	char	**content;
	int		index;

	content = extract_content(path);
	if (!content)
		return (write(1, "Error\nInvalid file\n", 20), 0);
	if (!check_content(content) || !check_texturing(content, game))
		return (free_darray(content), 0);
	index = check_for_map(content);
	if (!index || !parse_map(game, content + index, index))
		return (free_darray(content), 0);
	free_darray(content);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
		(write(1, "Error\nUsage: ./cub3d <path_to_cub_file>\n", 35), exit(EF));
	if (ft_strnstr(argv[1], ".cub", 5))
		(write(1, "Error\nInvalid file extension\n", 30), exit(EF));
	ft_memset(&game, 0, sizeof(t_data));
	if (!parse_cub(argv[1], &game))
		(free(&game),write(1, "Error\nParsing failed\n", 22), exit(EF));
}
