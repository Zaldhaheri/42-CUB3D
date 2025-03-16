
#include "../include/cub3d.h"

void	reverse_map(char **map)
{
	int		index;
	int		jindex;
	char	*store;

	index = 0;
	jindex = 0;
	while (map[index])
		index++;
	while (index > jindex)
	{
		store = map[--index];
		map[index] = map[jindex];
		map[jindex++] = store;
	}
}

int	is_texture_or_color_line(const char *line)
{
	return (ft_strnstr(line, "NO", 2) || ft_strnstr(line, "SO", 2)
		|| ft_strnstr(line, "WE", 2) || ft_strnstr(line, "EA", 2)
		|| ft_strnstr(line, "F", 1) || ft_strnstr(line, "C", 1));
}

int	check_for_map(char **file_data)
{
	int	line_index;

	line_index = 0;
	while (file_data[line_index])
	{
		if (is_texture_or_color_line(file_data[line_index]))
		{
			line_index++;
			continue ;
		}
		if (ft_strchr(file_data[line_index], '1')
			|| ft_strchr(file_data[line_index], '0'))
			return (line_index);
		line_index++;
	}
	return (0);
}

int	atoi_colors(t_data *game, char **colors, char texture)
{
	int color[3];
	int index;

	index = 0;
	while (index < 3)
	{
		color[index] = ft_atoi(colors[index]);
		if (color[index] < 0 || color[index] > 255)
			return (0);
		index++;
	}
	if (texture == 'F')
		game->parsing->f = (color[0] << 16) | (color[1] << 8) | color[2];
	else if (texture == 'C')
		game->parsing->c = (color[0] << 16) | (color[1] << 8) | color[2];
	else
		return (0);
	return (1);
}