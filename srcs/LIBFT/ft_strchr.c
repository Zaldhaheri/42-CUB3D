/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:27:05 by mbabayan          #+#    #+#             */
/*   Updated: 2025/04/02 17:51:47 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * function finds the first occurrence of c in the whole string.
 */
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while ((char)c != *s)
	{
		if (!*s)
			return (NULL);
		s++;
	}
	return ((char *)s);
}
