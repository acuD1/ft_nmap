/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:32 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 17:06:40 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "str.h"

size_t		ft_strcspn(const char *s, const char *charset)
{
	size_t		i;
	const char	*c;

	i = 0;
	while (*s)
	{
		c = charset;
		while (*c)
		{
			if (*s == *c)
				return (i);
			c++;
		}
		s++;
		i++;
	}
	return (i);
}
