/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:40:55 by mbabayan          #+#    #+#             */
/*   Updated: 2025/05/20 15:24:36 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		index;
	char	*new_str;

	index = 0;
	if (!s || !f)
		return (NULL);
	new_str = ft_strdup(s);
	if (!new_str)
		return (NULL);
	while (new_str[index])
	{
		new_str[index] = f(index, new_str[index]);
		index++;
	}
	return (new_str);
}
