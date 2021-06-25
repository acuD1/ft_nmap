/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stckpopnode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:24 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:24 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "libft.h"

t_list	*ft_stckpopnode(t_stack *stack)
{
	t_list		*holder;

	if (!stack->head)
		return (NULL);
	holder = stack->head;
	stack->head = stack->head->next;
	holder->next = NULL;
	--stack->size;
	return (holder);
}
