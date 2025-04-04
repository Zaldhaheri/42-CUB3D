/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:59:02 by mbabayan          #+#    #+#             */
/*   Updated: 2025/03/16 17:05:07 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * function that returns the line after allocating space for the line
 * and 
 */
char	*ft_get_line(char *conserve)
{
	int		index;
	char	*line;

	index = 0;
	if (!conserve[index])
		return (NULL);
	while (conserve[index] != '\0' && conserve[index] != '\n')
		index++;
	line = malloc(sizeof(char) * (index + 1 + (conserve[index] == '\n')));
	if (!line)
		return (NULL);
	index = 0;
	while (conserve[index] != '\0' && conserve[index] != '\n')
	{
		line[index] = conserve[index];
		index++;
	}
	if (conserve[index] == '\n')
	{
		line[index] = conserve[index];
		index++;
	}
	line[index] = '\0';
	return (line);
}

/*
 * function that returns the rest of the string
 */
char	*ft_save(char *conserve)
{
	int		index;
	int		index2;
	char	*buffer;

	index = 0;
	index2 = 0;
	while (conserve[index] != '\0' && conserve[index] != '\n')
		index++;
	if (!conserve[index])
	{
		free(conserve);
		return (NULL);
	}
	buffer = malloc(sizeof(char) * ((ft_strlen(conserve) - index) + 1));
	if (!buffer)
		return (NULL);
	index++;
	while (conserve[index] != '\0')
		buffer[index2++] = conserve[index++];
	buffer[index2] = '\0';
	free(conserve);
	return (buffer);
}
