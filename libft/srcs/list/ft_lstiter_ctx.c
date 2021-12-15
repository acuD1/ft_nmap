/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_ctx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:22 by cempassi          #+#    #+#             */
/*   Updated: 2021/12/15 23:10:29 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstiter_ctx(t_list *lst, void *context
				, int (*f)(void *data, void* context))
{
	if (lst)
	{
		if (f(lst->data, context) == FAILURE)
			return (FAILURE);
		return (ft_lstiter_ctx(lst->next, context, f));
	}
	return (SUCCESS);
}
