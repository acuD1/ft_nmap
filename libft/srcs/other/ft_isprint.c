/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:27 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 17:23:54 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"

int		ft_isprint(int c)
{
	if (c == '\n')
		return (1);
	return ((c >= 32 && c <= 126 && (c ^ 0x80)));
}
