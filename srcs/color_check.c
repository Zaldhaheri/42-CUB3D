#include "../include/cub3d.h"

int	setting_color(t_data *data, char *line)
{
	char **split;
	char **colors;
	int total;
	int color_channels;

	total = 0;
	color_channels = count_color_channels(line);
	colors = ft_split(line, ',');
	if (color_channels != 2 || !colors || !colors[0] || !colors[1] || !colors[2]
		|| colors[3])
		return (write(1, "Error\nInvalid color\n", 20), 0);
	split = ft_split(colors[0], ' ');
	if (string_compare(split[0], "F") == 0)
		total = atoi_colors(data, colors, 'F');
	else if (string_compare(split[0], "C") == 0)
		total = atoi_colors(data, colors, 'C');
	else
		total = printf("Error: Unknown color identifier\n") - 31;
	return (free_darray(split), free_darray(colors), total);
}