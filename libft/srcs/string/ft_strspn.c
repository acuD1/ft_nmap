/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:34 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 17:18:40 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strspn(const char *s, const char *charset)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (ft_strchr(charset, *s) == NULL)
			return (i);
		s++;
		i++;
	}
	return (i);
}
