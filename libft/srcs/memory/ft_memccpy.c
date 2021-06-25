/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:25 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 18:16:23 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "memory.h"
#pragma clang diagnostic ignored "-Wcast-qual"
#pragma clang diagnostic ignored "-Wpointer-arith"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	if (!n)
		return (NULL);
	*(unsigned char *)dst = *(unsigned char *)src;
	if (*(unsigned char *)src == (unsigned char)c)
		return ((unsigned char *)dst + 1);
	return (n == 1 ? NULL : ft_memccpy(++dst, ++src, c, --n));
}
