/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:25 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 17:20:14 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "memory.h"

static void	ft_init(void *s, size_t n)
{
	if (!n)
		return ;
	*((char *)s) = 0;
	while (--n > 0)
		((char *)s)[n] = '\0';
}

void		*ft_memalloc(size_t size)
{
	void	*ptr;

	if (!size || !(ptr = malloc(size)))
		return (NULL);
	ft_init(ptr, size);
	return (ptr);
}
