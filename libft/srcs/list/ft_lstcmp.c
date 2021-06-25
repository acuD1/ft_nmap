/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:21 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:21 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

/*
** The return of the function pointer must be null if EQ, greater or smaller
** than 0 if not EQ.
*/

int		ft_lstcmp(t_list *lst1, t_list *lst2, int (*f)(void *, void *))
{
	if (!lst1 && !lst2)
		return (0);
	if ((lst1 && !lst2) || (!lst1 && lst2))
		return (-1);
	if (f(lst1->data, lst2->data))
		return (-1);
	return (ft_lstcmp(lst1->next, lst2->next, f));
}
