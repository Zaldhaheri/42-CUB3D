/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:23:22 by mbabayan          #+#    #+#             */
/*   Updated: 2025/05/18 12:19:27 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *haystack, char const *needle, int n)
{
	int	j;

	if (!haystack && !n)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && n--)
	{
		j = -1;
		while (++j <= n && *(haystack + j) == *(needle + j))
			if ((*(needle + j + 1) == '\0'))
				return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
