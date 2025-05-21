/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:20:01 by zaldhahe          #+#    #+#             */
/*   Updated: 2025/05/21 11:40:59 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*trim_line(char *line)
{
	ssize_t	i;
	char	*str;

	i = 0;
	if (!line || line[0] == '\0' || line[1]== '\0')
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	str = ft_substr(line, i + 1, ft_strlen(line + i + 1));
	if (!str || *str == '\0')
	{
		free(str);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (str);
}

char	*read_buffer(int fd, char *str, char *buffer)
{
	ssize_t	s_bytes;
	char	*temp;

	s_bytes = 1;
	while (s_bytes > 0)
	{
		s_bytes = read(fd, buffer, BUFFER_SIZE);
		if (s_bytes == -1)
		{
			free(str);
			return (NULL);
		}
		else if (s_bytes == 0)
			break ;
		buffer[s_bytes] = '\0';
		if (!str)
			str = ft_strdup("");
		temp = str;
		str = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0))
	{
		free(buffer);
		free(str);
		buffer = NULL;
		str = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = read_buffer(fd, str, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	str = trim_line(line);
	return (line);
}

// int main()
// {
// 	int fd = open("h.txt", O_RDONLY);
// 	printf("fd: %d\n", fd);
// 	printf("gnl[1]: %s\n", get_next_line(fd));
// 	printf("gnl[2]: %s\n", get_next_line(fd));
// 	printf("gnl[3]: %s\n", get_next_line(fd));
// }