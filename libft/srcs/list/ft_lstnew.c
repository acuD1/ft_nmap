/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:23 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:23 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *data, size_t data_size)
{
	t_list		*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!data)
	{
		new->data = NULL;
		new->data_size = 0;
		new->next = NULL;
		return (new);
	}
	if (!(new->data = malloc(data_size)))
	{
		free(new);
		return (NULL);
	}
	new->data_size = data_size;
	ft_memcpy(new->data, data, data_size);
	new->next = NULL;
	return (new);
}
