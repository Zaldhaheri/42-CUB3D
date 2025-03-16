/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:58:39 by mbabayan          #+#    #+#             */
/*   Updated: 2025/03/16 17:04:29 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * function that reads the file and stores content in static var
 */
char	*ft_readfile(char *conserve, int fd)
{
	int		rd;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	rd = 1;
	while (ft_strchr(conserve, '\n') == 0 && rd != 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
		{
			if (conserve != NULL)
				free(conserve);
			free(buffer);
			return (NULL);
		}
		buffer[rd] = '\0';
		conserve = ft_strjoin(conserve, buffer);
	}
	free(buffer);
	return (conserve);
}

/*
 * function read file line by line, it first checks if fd
 * is valid, if the buffer size is valid and if the buffer
 * size is not bigger than the max int value and then it
 * calls the ft_readfile function to read the file and

 */
char	*get_next_line(int fd)
{
	char		*print;
	static char	*conserve;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	conserve = ft_readfile(conserve, fd);
	if (!conserve)
		return (NULL);
	print = ft_get_line(conserve);
	conserve = ft_save(conserve);
	return (print);
}
