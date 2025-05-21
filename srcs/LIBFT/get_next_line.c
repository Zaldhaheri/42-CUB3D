/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:08:20 by mbabayan          #+#    #+#             */
/*   Updated: 2025/05/21 14:38:14 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_newbuf(char *old_buf, char *curr_buf)
{
	char	*new_buf;

	new_buf = ft_strjoin(old_buf, curr_buf);
	if (!new_buf)
	{
		free(old_buf);
		return (NULL);
	}
	free(old_buf);
	return (new_buf);
}

char	*line_fetch(char *buffer)
{
	char	*line;
	size_t	line_len;
	size_t	i;

	if (!*buffer)
		return (NULL);
	i = 0;
	line_len = get_line_len(buffer);
	line = malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n' && buffer[i])
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_buf(char *buffer)
{
	char	*new_buf;
	size_t	remaining;
	size_t	i;

	if (!*buffer)
	{
		free(buffer);
		return (NULL);
	}
	remaining = 0;
	i = 0;
	while (buffer[remaining] && buffer[remaining] != '\n')
		remaining++;
	if (!malloc_buf(&new_buf, ft_strlen(buffer) - remaining + 1))
		return (NULL);
	if (buffer[remaining] == '\n' && buffer[remaining])
		remaining++;
	while (buffer[remaining])
		new_buf[i++] = buffer[remaining++];
	new_buf[i] = '\0';
	free(buffer);
	return (new_buf);
}

char	*populate_buffer(int fd, char *buffer)
{
	char	*temp_buf;
	int		b_read;

	if (!buffer && !malloc_buf(&buffer, sizeof(char)))
		return (NULL);
	b_read = 1;
	if (!malloc_buf(&temp_buf, (size_t)BUFFER_SIZE + 1))
		return (NULL);
	while (b_read > 0 && !ft_strchr(buffer, '\n'))
	{
		b_read = read(fd, temp_buf, BUFFER_SIZE);
		if (b_read < 0)
		{
			if (temp_buf)
				free(temp_buf);
			if (buffer)
				free(buffer);
			return (NULL);
		}
		temp_buf[b_read] = '\0';
		buffer = join_newbuf(buffer, temp_buf);
	}
	free(temp_buf);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || (size_t)BUFFER_SIZE >= 2147483647)
	{
		return (NULL);
	}
	buffer = populate_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = line_fetch(buffer);
	buffer = update_buf(buffer);
	return (line);
}