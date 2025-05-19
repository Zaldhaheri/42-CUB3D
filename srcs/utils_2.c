
#include "../include/cub3d.h"

/*
 * Function to free a double pointer array
 * Returns 0 on success
 */
int	free_darray(char **darray)
{
	int	i;

	i = -1;
	while (darray && darray[++i])
		free(darray[i]);
	free(darray);
	return (0);
}