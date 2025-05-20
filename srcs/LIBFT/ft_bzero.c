/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:18:56 by mbabayan          #+#    #+#             */
/*   Updated: 2025/05/20 15:26:51 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Sets memory of a block to 0 no matter what
*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
