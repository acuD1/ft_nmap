/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:34 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 17:18:28 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#pragma clang diagnostic ignored "-Wcast-qual"


static	char	*search(const char *s, int c, int len)
{
	if (c == '\0')
		return ((char *)(s + 1));
	if (len == 0)
		return (NULL);
	return (*s == (char)c ? (char *)s : search(--s, c, --len));
}

char			*ft_strrchr(const char *s, int c)
{
	size_t		len;

	if (!*s)
		return (*s == (char)c ? (char *)s : NULL);
	len = ft_strlen(s);
	return (search(&s[len - 1], c, (int)len));
}
