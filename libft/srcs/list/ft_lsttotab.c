/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttotab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:23 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:23 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stdlib.h>

char	**ft_lsttotab(t_list *lst, char *(*f)(void *))
{
	char	**result;
	size_t	lstlen;
	size_t	index;

	lstlen = ft_lstlen(lst);
	result = malloc(sizeof(char *) * (lstlen + 1));
	index = 0;
	while (index < lstlen)
	{
		result[index++] = f(lst->data);
		lst = lst->next;
	}
	result[index] = NULL;
	return (result);
}
