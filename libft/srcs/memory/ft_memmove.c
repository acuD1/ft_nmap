/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:25 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 17:23:05 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#pragma clang diagnostic ignored "-Wcast-qual"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (n)
	{
		if ((unsigned long)dst < (unsigned long)src)
			return (ft_memcpy(dst, src, n));
		else
		{
			while (--n > 0)
				((unsigned char *)dst)[n] = ((unsigned char *)src)[n];
			*(unsigned char *)dst = *(unsigned char *)src;
		}
	}
	return (dst);
}
