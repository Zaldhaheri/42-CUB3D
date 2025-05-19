#include "../include/cub3d.h"

int	find_start(char **f_data)
{
	int	index;

	index = -1;
	while (f_data[++index])
	{
		if (ft_strnstr(f_data[index], "NO", 2)
			|| ft_strnstr(f_data[index], "SO", 2)
			|| ft_strnstr(f_data[index], "WE", 2)
			|| ft_strnstr(f_data[index], "EA", 2)
			|| ft_strnstr(f_data[index], "F", 1)
			|| ft_strnstr(f_data[index], "C", 1))
			continue ;
		if (ft_strchr(f_data[index], '1') || ft_strchr(f_data[index], '0'))
			return (index);
	}
	return (-1);
}

int	check_walls(t_data *data)
{
	int	index;
	int	jindex;
	int	width;
	int	height;

	index = -1;
	height = data->map_height;
	while (++index < height)
	{
		width = ft_strlen(data->map[index]);
		jindex = -1;
		while (++jindex < width)
			if (ft_strchr("0NSEWD", data->map[index][jindex])
				&& (!index || index + 1 == height || !jindex || jindex + 1 == width
				|| !ft_strchr("WESN10D", data->map[index - 1][jindex])
				|| !ft_strchr("WESN10D", data->map[index + 1][jindex])
				|| !ft_strchr("WESN10D", data->map[index][jindex - 1])
				|| !ft_strchr("WESN10D", data->map[index][jindex + 1])))
				return (printf("Error\nMap is not enclosed by walls\n"),
					free_darray(data->map), -1);
	}
	return (0);
}