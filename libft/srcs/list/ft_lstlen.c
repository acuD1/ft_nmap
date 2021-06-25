/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:22 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/23 14:47:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

size_t		ft_lstlen(t_list *lst)
{
	size_t		len;

	len = 0;
	if (!lst)
		return (len);
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}
