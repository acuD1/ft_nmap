/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:25 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 17:22:31 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "memory.h"
#pragma clang diagnostic ignored "-Wcast-qual"
#pragma clang diagnostic ignored "-Wpointer-arith"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (!n)
		return (0);
	return (*((unsigned char *)s1) != *((unsigned char *)s2) || n == 1 ?
			*((unsigned char *)s1) - *((unsigned char *)s2) :
			ft_memcmp(++s1, ++s2, --n));
}
