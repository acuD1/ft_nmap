/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:58:34 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/07 13:41:55 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

uint16_t    in_cksum(void *buffer, size_t len)
{
    uint16_t *tmp   = (uint16_t *)buffer;
    uint32_t sum    = 0;

    while (len > 1)
    {
        sum += *tmp++;
        len -= 2;
    }

    if (len > 0)
        sum += *(uint8_t *)tmp;

    while (sum >> 16)
        sum = (sum & 0xFFFF) + (sum >> 16);

    return ((uint16_t)~sum);
}

bool   is_tcp_scan(uint8_t scan)
{
    if (scan & SCAN_SYN)
        return (true);
    if (scan & SCAN_ACK)
        return (true);
    if (scan & SCAN_FIN)
        return (true);
    if (scan & SCAN_XMAS)
        return (true);
    if (scan & SCAN_NULL)
        return (true);
    return (false);
}

uint8_t is_loopback(struct sockaddr_in *addr)
{
    uint8_t first_byte = (uint8_t)(addr->sin_addr.s_addr);
    if (first_byte == (uint8_t)0x7f || addr->sin_addr.s_addr == 0)
        return (SUCCESS);
    return (FAILURE);
}
