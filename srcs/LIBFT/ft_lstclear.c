/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:18:54 by mbabayan          #+#    #+#             */
/*   Updated: 2023/11/20 14:19:00 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *holder;

	if (!*lst)
		return ;
	while (*lst)
	{
		holder = (*lst) -> next;
		ft_lstdelone(*lst, del);
		*lst = holder;
	}
	free(*lst);
}
