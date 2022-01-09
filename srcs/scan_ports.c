/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_ports.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:40:30 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/09 09:37:31 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

uint8_t scan_ports(t_thread *thread)
{
    if (thread->scan & SCAN_SYN)
    {
        if (send_tcp(thread, S_SYN) != SUCCESS)
            return (FAILURE);
    }
    if (thread->scan & SCAN_FIN)
    {
        if (send_tcp(thread, S_FIN) != SUCCESS)
            return (FAILURE);
    }
    if (thread->scan & SCAN_ACK)
    {
        if (send_tcp(thread, S_ACK) != SUCCESS)
            return (FAILURE);
    }
    if (thread->scan & SCAN_XMAS)
    {
        if (send_tcp(thread, S_XMAS) != SUCCESS)
            return (FAILURE);
    }
    if (thread->scan & SCAN_NULL)
    {
        if (send_tcp(thread, S_NULL) != SUCCESS)
            return (FAILURE);
    }
    if (thread->scan & SCAN_UDP)
    {
        if (send_udp(thread, S_UDP) != SUCCESS)
            return (FAILURE);
    }
    return (SUCCESS);
}
