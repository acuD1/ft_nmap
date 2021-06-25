/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfold.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedricmpassi <cempassi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 01:12:02 by cedricmpa         #+#    #+#             */
/*   Updated: 2020/10/28 01:16:29 by cedricmpa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "list.h"

void ft_lstfold(t_list *lst, void *acc, void (*f)(void *acc, void *data))
{
	while(lst)
	{
		f(acc, lst->data);
		lst = lst->next;
	}
}
