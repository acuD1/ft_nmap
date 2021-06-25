/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:32 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 17:06:05 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "str.h"
#pragma clang diagnostic ignored "-Wcast-qual"

int		ft_strcmp(const char *s1, const char *s2)
{
	return (*s1 != *s2 || (!*s1 && !*s2) ?
			*(unsigned char *)s1 - *(unsigned char *)s2 :
			ft_strcmp(s1 + 1, s2 + 1));
}
