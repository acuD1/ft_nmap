/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:21 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:21 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

#include "libft.h"

int		ft_lstaddback(t_list **alst, t_list *new)
{
	t_list	*holder;

	if (!new)
		return (-1);
	holder = *alst == NULL ? NULL : *alst;
	if (holder)
	{
		while (holder->next != NULL)
			holder = holder->next;
		holder->next = new;
		return (1);
	}
	*alst = new;
	return (1);
}
