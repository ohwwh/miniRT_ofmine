/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelnode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <hoh@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:26:06 by hoh               #+#    #+#             */
/*   Updated: 2022/07/27 13:26:13 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelnode(t_list **lst, t_list *target, void (*del)(void *))
{
	t_list	*delnode;
	t_list	*prev;

	prev = 0;
	delnode = *lst;
	while (delnode)
	{
		if (delnode == target)
		{
			if (prev)
				prev->next = delnode->next;
			else
				*lst = delnode->next;
			del(delnode -> content);
			free(delnode);
			break ;
		}
		prev = delnode;
		delnode = delnode->next;
	}
}
