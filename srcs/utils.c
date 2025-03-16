#include "../include/cub3d.h"

int	free_darray(char **darray)
{
	int	index;

	index = -1;
	while (darray && darray[++index])
		free(darray[index]);
	free(darray);
	return (0);
}

void	trim_end(char *string, char *set)
{
	int	end;

	if (!string && !set)
		return ;
	end = ft_strlen(string) - 1;
	while (end && ft_strchr(set, string[end]))
		end--;
	string[end + 1] = '\0';
}

int	count_color_channels(char *line)
{
	int	index;

	index = 0;
	while (*line)
	{
		if (*line == ',')
			index++;
		line++;
	}
	return (index);
}

char	**split_color_channels(char *line)
{
	int	index;
	int	flag;

	index = 0;
	flag = 0;
	while (line[index] == ' ')
		index++;
	if (line[index] == 'F' || line[index] == 'C')
	{
		index++;
		while (line[index] == ' ' && flag++)
			index++;
	}
	if (flag != 1)
		return (NULL);
	return (ft_split(line + index, ','));
}

int	string_compare(const char *string1, const char *string2)
{
	while (*string1 && *string2 && *string1 == *string2)
	{
		string1++;
		string2++;
	}
	return ((unsigned char)*string1 - (unsigned char)*string2);
}