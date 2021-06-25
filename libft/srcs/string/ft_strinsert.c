/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:32 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/23 14:46:21 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdlib.h>

char		*ft_strinsert(char **str, char c, size_t index)
{
	char		*tmp;
	char		*cpy;
	size_t		len;
	size_t		i;

	if (!str || !*str)
		return (NULL);
	i = 0;
	cpy = *str;
	len = ft_strlen(*str) + 2;
	if (!(tmp = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	while (--len)
	{
		if (i == index)
			tmp[i] = c;
		else
			tmp[i] = *cpy++;
		i++;
	}
	tmp[i] = '\0';
	ft_strdel(str);
	return (tmp);
}
