/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:22:25 by mbabayan          #+#    #+#             */
/*   Updated: 2025/05/20 15:22:33 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
 * Function to count the number of lines in a file
 * Returns the number of lines or -1 on error
 */
static int	count_lines(const char *path)
{
	int		fd;
	char	*line;
	int		count_lines;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	count_lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		count_lines++;
	}
	close(fd);
	return (count_lines);
}

/*
 * Function to extract the content of a file into an array of strings
 * Returns a pointer to the array or NULL on error
 */
char	**extract_f(const char *path)
{
	int		fd;
	char	**content;
	char	*line;
	int		index;

	line = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	content = (char **)ft_calloc(count_lines(path) + 1, 8);
	if (content == NULL)
		return (NULL);
	index = 0;
	line = get_next_line(fd);
	while (line)
	{
		content[index++] = line;
		line = get_next_line(fd);
	}
	content[index] = NULL;
	close(fd);
	return (content);
}

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
