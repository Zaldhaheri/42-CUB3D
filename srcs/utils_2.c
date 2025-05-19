
#include "../include/cub3d.h"


int	free_darray(char **darray)
{
	int	i;

	i = -1;
	while (darray && darray[++i])
		free(darray[i]);
	free(darray);
	return (0);
}