/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:33 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 17:08:08 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t					i;
	size_t					j;
	size_t					len;
	size_t					n;

	n = size;
	i = 0;
	j = 0;
	len = ft_strlen(dest) + ft_strlen(src);
	while (n-- != 0 && dest[i] != '\0')
		i++;
	n = size - i;
	if (!n)
		return (size + ft_strlen(src));
	while (src[j] && n > 0)
	{
		if (n > 1)
			dest[i++] = src[j++];
		n--;
	}
	dest[i] = '\0';
	return (len);
}
