/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:09:12 by mbabayan          #+#    #+#             */
/*   Updated: 2025/05/21 14:38:03 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(const char *str)
{
	size_t	length;

	if (!str)
		return (0);
	length = 0;
	while (str[length])
		length++;
	return (length);
}

char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	if (!(unsigned char)c)
		return ((char *)&s[ft_strlen((char *)s)]);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

size_t	get_line_len(char *buffer)
{
	size_t	line_len;

	line_len = 0;
	if (!buffer)
		return (line_len);
	while (buffer[line_len] != '\n' && buffer[line_len])
		line_len++;
	if (buffer[line_len] == '\n' && buffer[line_len])
		line_len++;
	return (line_len);
}

void	*malloc_buf(char **pbfr, size_t mal_size)
{
	size_t	i;
	char	*tmp;

	*pbfr = malloc(sizeof(char) * mal_size);
	if (!*pbfr)
		return (NULL);
	i = 0;
	tmp = *pbfr;
	while (i < mal_size)
		tmp[i++] = 0;
	return ((char *)*pbfr);
}