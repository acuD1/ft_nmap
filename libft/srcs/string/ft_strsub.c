/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:34 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/23 14:51:22 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdlib.h>

static char	*ft_ncpy(char *dst, const char *src, size_t len)
{
	char	*d;

	d = dst;
	if (!len)
		return (dst);
	while (*src && len)
	{
		*d++ = *src++;
		len--;
	}
	while (len)
	{
		*d++ = '\0';
		len--;
	}
	return (dst);
}

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*sub;

	if (!s)
		return (NULL);
	if (!(sub = (char *)malloc(len + 1)))
		return (NULL);
	sub = ft_ncpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}
