/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:34 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 17:17:41 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#pragma clang diagnostic ignored "-Wcast-qual"


char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (*needle == '\0')
		return ((char *)haystack);
	if (*haystack == '\0' || len == 0 || ft_strlen(needle) > len)
		return (NULL);
	return (ft_strncmp(haystack, needle, ft_strlen(needle)) == 0 ?
			(char *)haystack : ft_strnstr(++haystack, needle, --len));
}
