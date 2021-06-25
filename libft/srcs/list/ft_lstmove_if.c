/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmove_if.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 18:20:58 by cedricmpa         #+#    #+#             */
/*   Updated: 2021/06/24 17:00:01 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		return_manager(int mask)
{
	static int	check = 0;
	int			holder;

	if (mask == 1)
		return (check = 1);
	else if (mask == 0)
	{
		holder = check;
		check = 0;
		return (holder);
	}
	return (check);
}

static t_list	*mover(t_list *current, t_list **dst, void *to_find, t_cmp cmp)
{
	t_list *tmp;

	if (!current)
		return (NULL);
	else if (cmp(current->data, to_find))
	{
		tmp = current->next;
		current->next = NULL;
		ft_lstaddback(dst, current);
		tmp = mover(tmp, dst, to_find, cmp);
		return_manager(1);
		return (tmp);
	}
	else
	{
		current->next = mover(current->next, dst, to_find, cmp);
		return (current);
	}
}

int 			ft_lstmove_if(t_list **src, t_list **dst, void *to_find, t_cmp cmp)
{
	t_list *tmp;

	if (!src || !*src || !cmp)
		return (return_manager(0));
	if (cmp((*src)->data, to_find))
	{
		tmp = (*src)->next;
		(*src)->next = NULL;
		ft_lstaddback(dst, (*src));
		(*src) = tmp;
		return_manager(1);
		return (ft_lstmove_if(src, dst, to_find, cmp));
	}
	if ((*src)->next)
		(*src)->next = mover((*src)->next, dst, to_find, cmp);
	return (return_manager(0));
}
