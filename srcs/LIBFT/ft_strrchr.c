/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:21:02 by mbabayan          #+#    #+#             */
/*   Updated: 2024/03/28 15:16:38 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *concerve, int c)
{
	int	i;

	i = 0;
	if (!concerve)
		return (0);
	if ((char)c == '\0')
		return (&concerve[ft_strlen(concerve)]);
	while (concerve[i])
	{
		if (concerve[i] == (char)c)
			return (&concerve[i]);
		i++;
	}
	return (0);
}
