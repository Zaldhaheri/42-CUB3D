#include "../include/cub3d.h"


int	count_chars(const char *str, char character)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == character)
			count++;
		str++;
	}
	return (count);
}

char	**color_split(char *s)
{
	int	index;
	int	flag;

	index = 0;
	index = 0;
	flag = 0;
	while (s[index] == ' ')
		index++;
	if (s[index] == 'F' || s[index] == 'C')
	{
		index++;
		while (s[index] == ' ' && flag++)
			index++;
	}
	if (flag != 1)
		return (NULL);
	return (ft_split(s + index, ','));
}


int	use_atoi(t_data *data, char **colors, char texture)
{
	int	color[3];

	color[0] = ft_atoi(colors[0]);
	color[1] = ft_atoi(colors[1]);
	color[2] = ft_atoi(colors[2]);
	if (color[0] < 0 || color[0] > 255 || color[1] < 0 || color[1] > 255
		|| color[2] < 0 || color[2] > 255)
		return (0);
	if (texture == 'F')
		data->textures.floor = color[0] << 16 | color[1] << 8 | color[2];
	else if (texture == 'C')
		data->textures.ceiling = color[0] << 16 | color[1] << 8 | color[2];
	else
		return (0);
	return (1);

}