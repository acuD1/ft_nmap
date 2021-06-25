/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_ctx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:22 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:22 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstiter_ctx(t_list *lst, void *context
				, int (*f)(void *context, void *data))
{
	if (lst)
	{
		if (f(context, lst->data) == FAILURE)
			return (FAILURE);
		return (ft_lstiter_ctx(lst->next, context, f));
	}
	return (SUCCESS);
}
