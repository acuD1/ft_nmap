/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stckpushnode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:24 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:24 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stckpushnode(t_stack *stack, t_list *node)
{
	if (!stack || !node)
		return (-1);
	node->next = stack->head;
	stack->head = node;
	stack->size += 1;
	return (0);
}
