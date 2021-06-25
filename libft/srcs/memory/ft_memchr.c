/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:25 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 17:22:05 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "memory.h"
#pragma clang diagnostic ignored "-Wcast-qual"
#pragma clang diagnostic ignored "-Wpointer-arith"

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (!n)
		return (NULL);
	return (*((const unsigned char *)s) == (unsigned char)c && n > 0 ?
			(void *)s : ft_memchr(++s, c, --n));
}
