/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 12:42:44 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/24 18:36:52 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

int32_t ft_atoi(const char *s)
{
	size_t	i;
	int32_t	nb;
	int8_t	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+' || s[i] == '-')
		sign *= (s[i++] == '-' ? -1 : 1);
	while (s[i] >= '0' && s[i] <= '9')
		nb = (nb * 10) + (s[i++] - '0');
	return (sign * nb);
}
