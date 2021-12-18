/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfold.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedricmpassi <cempassi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 01:12:02 by cedricmpa         #+#    #+#             */
/*   Updated: 2021/12/18 15:30:43 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "list.h"

void ft_lstfold(t_list *lst, void *acc, void (*f)(void *data, void *acc))
{
	while(lst)
	{
		f(lst->data, acc);
		lst = lst->next;
	}
}
