/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:04:46 by mbabayan          #+#    #+#             */
/*   Updated: 2025/05/20 15:23:44 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * function that takes as a parameter an element and frees the memory of the
 * elements content using the function ’del’ given as a parameter and free
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}
