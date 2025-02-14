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