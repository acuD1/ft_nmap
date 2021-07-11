/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:58:34 by arsciand          #+#    #+#             */
/*   Updated: 2021/07/09 18:51:20 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

uint16_t in_cksum(const void *buffer, size_t len)
{
	uint16_t *tmp   = (uint16_t*)buffer;
	uint32_t sum    = 0;

	while (len > 1)
	{
		sum += *tmp++;
		len -= 2;
	}

	if (len > 0)
		sum += *(uint8_t*)tmp;

	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	return ~sum;
}

