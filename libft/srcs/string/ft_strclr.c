/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:31 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 17:05:20 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <unistd.h>

static void		ft_init(void *s, size_t n)
{
	if (!n)
		return ;
	*((char *)s) = 0;
	while (--n > 0)
		((char *)s)[n] = '\0';
}

static size_t	ft_len(const char *s)
{
	size_t	i;

	if (*s == '\0')
		return (0);
	i = 0;
	while (s[++i])
		;
	return (i);
}

void			ft_strclr(char *c)
{
	if (!c)
		return ;
	ft_init(c, ft_len(c));
	return ;
}
