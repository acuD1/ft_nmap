/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:31 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 17:02:30 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "other.h"
#include <stdlib.h>
#include <stdint.h>

uint8_t			ft_isnumeric(char *str)
{
	if (str == NULL)
		return (0);
	if (*str == '-')
		++str;
	if (*str == '\0')
		return (0);
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		++str;
	}
	return (1);
}
