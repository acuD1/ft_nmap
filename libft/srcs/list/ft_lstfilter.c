/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfilter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:22 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:22 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstfilter(t_list *lst, void *to_find, t_cmp filter, t_cmp cpy)
{
	t_list	*new;
	t_list	*node;

	new = NULL;
	while (lst)
	{
		if (filter(lst->data, to_find))
		{
			node = ft_lstnew(lst->data, lst->data_size);
			cpy(lst->data, node->data);
			ft_lstaddback(&new, node);
		}
		lst = lst->next;
	}
	return (new);
}
