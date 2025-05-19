/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:19:18 by zaldhahe          #+#    #+#             */
/*   Updated: 2025/05/16 15:54:54 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char) c)
			break ;
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}

char	*gnl_strdup(const char *str)
{
	char	*dup;
	int		i;

	i = 0;
	dup = (char *) malloc(ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char			*r;
	size_t			i;
	unsigned int	strlen;

	i = 0;
	strlen = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= strlen)
		return (ft_strdup(""));
	if (len + start >= strlen)
		len = strlen - start;
	r = malloc(sizeof(char) * len + 1);
	if (!r)
		return (NULL);
	while (s[start] && i < len)
		r[i++] = s[start++];
	r[i] = '\0';
	return (r);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;
	char	*r;

	i = 0;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	r = (char *) malloc(sizeof(char) * (len1 + len2 + 1));
	if (!r)
		return (NULL);
	while (s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	while (s2[j])
		r[i++] = s2[j++];
	r[i] = '\0';
	return (r);
}