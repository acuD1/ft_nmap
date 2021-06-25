/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:22 by cempassi          #+#    #+#             */
/*   Updated: 2020/10/27 18:16:25 by cedricmpa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *lst, void *to_find, t_cmp f)
{
	if (lst == NULL)
		return (NULL);
	return (f(lst->data, to_find) ? lst : ft_lstfind(lst->next, to_find, f));
}
