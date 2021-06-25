/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:23 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 16:59:35 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	mapper(t_list *lst, t_list **map, void *context, t_lstmap func)
{
	t_list	*node;

	node = NULL;
	if (!lst)
		return (0);
	if ((node = func(context, lst->data)) == NULL)
		return (-1);
	ft_lstaddback(map, node);
	return (mapper(lst->next, map, context, func));
}

t_list		*ft_lstmap(t_list *lst, void *context, t_lstmap func, t_del del)
{
	t_list	*map;

	if (func == NULL)
		return (NULL);
	map = NULL;
	if (mapper(lst, &map, context, func))
	{
		ft_lstdel(&map, del);
		return (NULL);
	}
	return (map);
}
