/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stckpush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:24 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:24 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stckpush(t_stack *stack, void *data, size_t size)
{
	t_list	*node;

	if (!stack || !size)
		return (-1);
	if (!(node = ft_lstnew(data, size)))
		return (-1);
	ft_lstadd(&stack->head, node);
	stack->size += 1;
	return (0);
}
