/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:05:54 by mbabayan          #+#    #+#             */
/*   Updated: 2025/05/21 15:51:58 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * function locates the first occurrence of c in string s, until n bytes.
 */
void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)str;
	while (i < n)
	{
		if (ptr[i] == (unsigned char) c)
			return ((void *)(ptr + i));
		i++;
	}
	return (NULL);
}