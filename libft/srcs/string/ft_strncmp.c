/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:33 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 17:17:05 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "str.h"
#pragma clang diagnostic ignored "-Wcast-qual"


int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	return (*s1 != *s2 || (!*s1 && !*s2) || n == 1 ?
			*(unsigned char *)s1 - *(unsigned char *)s2 :
			ft_strncmp(++s1, ++s2, --n));
}
