#include "../include/cub3d.h"

int enclosed_check(t_data *data)
{
	int	index;
	int	jindex;

	index = 0;
	while (index < data->parsing->map_height)
	{
		jindex = 0;
		while (jindex < data->parsing->map_width)
		{
			if (data->parsing->map[index][jindex] == '0')
			{
				if (index == 0 || index == data->parsing->map_height - 1
					|| jindex == 0 || jindex == data->parsing->map_width - 1)
					return (write(1, "Error: Map not enclosed\n", 24), 0);
				if (data->parsing->map[index - 1][jindex] == ' '
					|| data->parsing->map[index + 1][jindex] == ' '
					|| data->parsing->map[index][jindex - 1] == ' '
					|| data->parsing->map[index][jindex + 1] == ' ')
					return (write(1, "Error: Map not enclosed\n", 24), 0);
			}
			jindex++;
		}
		index++;
	}
	return (1);
}

int	create_map(t_data *data, char **map)
{
	int	index;
	int	length;

	index = -1;
	while (map[++index])
	{
		length = ft_strlen(map[index]);
		if (length > data->parsing->map_width)
			data->parsing->map_width = length;
	}
	data->parsing->map = ft_calloc((data->parsing->map_height + 1),
			sizeof(char *));
	if (!data->parsing->map)
		return (write(1, "Error: Couldn't Allocate for map\n", 34), 0);
	index = -1;
	while (map[++index])
	{
		data->parsing->map[index] = malloc((data->parsing->map_width + 1)
				* sizeof(char));
		if (!data->parsing->map[index])
			return (free_darray(data->parsing->map), 0);
		data->parsing->map[index][data->parsing->map_height] = '\0';
		ft_memset(data->parsing->map[index], 32, data->parsing->map_width);
		ft_memcpy(data->parsing->map[index], map[index], ft_strlen(map[index]));
	}
	return (1);
}

void	set_player_data(t_data *data, char **content, int start, int index)
{
	data->plr->pos_x = start + 0.5;
	data->plr->pos_y = index + 0.5;
	if (content[start][index] == 'N')
		data->plr->orientation = 0;
	else if (content[start][index] == 'S')
		data->plr->orientation = 180;
	else if (content[start][index] == 'W')
		data->plr->orientation = 270;
	else if (content[start][index] == 'E')
		data->plr->orientation = 90;
}

int	check_chars(char **content, int start, t_data *data)
{
	int	index;

	index = 0;
	while (content[start][index])
	{
		if (ft_strchr("NSEW", content[start][index]))
		{
			set_player_data(data, content, start, index);
			content[start][index] = '0';
			data->plr->player_flag++;
			index++;
		}
		else if (!ft_strchr("01NSEW \t\n", content[start][index]))
			return (printf("Error: Invalid character: '%c' at [%d][%d]",
					content[start][index], start, index), 0);
		index++;
	}
	return (1);
}

int	parse_map(t_data *data, char **content, int start)
{
	start = -1;
	data->plr->player_flag = 0;
	while (content[data->parsing->map_height])
		data->parsing->map_height++;
	reverse_map(content);
	while (content[++start])
	{
		if (!content[start][0])
			return (write(1, "Error:\nBlank Line", 27), 0);
		if (!check_chars(content, start, data))
			return (0);
	}
	if (!create_map(data, content))
		return (0);
	if (data->plr->player_flag != 1 || enclosed_check(data))
		return (0);
	return (1);
}
