#include "../include/cub3d.h"

int	create_map(t_data *game, char **map)
{
	int	index;
	int	length;

	index = -1;
	while (map[++index])
	{
		length = ft_strlen(map[index]);
		if (length > game->parsing->map_width)
			game->parsing->map_width = length;
	}
	game->parsing->map = ft_calloc((game->parsing->map_height + 1),
			sizeof(char *));
	if (!game->parsing->map)
		return (write(1, "Error: Malloc failed\n", 22), 0);
	index = -1;
	while (map[++index])
	{
		game->parsing->map[index] = malloc((game->parsing->map_width + 1)
				* sizeof(char));
		if (!game->parsing->map[index])
			return (free_split(game->parsing->map), 0);
		game->parsing->map[index][game->parsing->map_height] = '\0';
		ft_memset(game->parsing->map[index], 32, game->parsing->map_width);
		ft_memcpy(game->parsing->map[index], map[index], ft_strlen(map[index]));
	}
	return (1);
}

void	set_player_data(t_data *game, char **content, int start, int index)
{
	game->plr->pos_x = start + 0.5;
	game->plr->pos_y = index + 0.5;
	if (content[start][index] == 'N')
		game->plr->orientation = 0;
	else if (content[start][index] == 'S')
		game->plr->orientation = 180;
	else if (content[start][index] == 'W')
		game->plr->orientation = 270;
	else if (content[start][index] == 'E')
		game->plr->orientation = 90;
}

int	check_chars(char **content, int start, t_data *game)
{
	int	index;

	index = 0;
	while (content[start][index])
	{
		if (ft_strchr("NSEW", content[start][index]))
		{
			set_player_data(game, content, start, index);
			content[start][index] = '0';
			game->plr->player_flag++;
			index++;
		}
		else if (!ft_strchr("01NSEW \t\n", content[start][index]))
			return (printf("Error: Invalid character: '%c' at [%d][%d]",
					content[start][index], start, index), 0);
		index++;
	}
	return (1);
}

int	parse_map(t_data *game, char **content, int start)
{
	start = -1;
	game->plr->player_flag = 0;
	while (content[game->parsing->map_height])
		game->parsing->map_height++;
	reverse_map(content);
	while (content[++start])
	{
		if (!content[start][0])
			return (write(1, "Error:\nBlank Line", 27), 0);
		if (!check_chars(content, start, game))
			return (0);
	}
	if (!create_map(game, content))
		return (0);
	if (game->plr->player_flag != 1 || enclosed_check(game))
		return (0);
	return (1);
}
