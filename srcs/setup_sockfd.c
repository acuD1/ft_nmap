/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sockfd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:45:11 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/09 09:22:52 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static uint8_t  socket_handler(struct sockaddr_in *dst, int *sockfd,
                               uint8_t protocol)
{
    if ((*sockfd = socket(dst->sin_family, SOCK_RAW, protocol)) == -1)
    {
        dprintf(STDERR_FILENO, "ft_nmap: socket(): %s", strerror(errno));
        return (FAILURE);
    }

    if (setsockopt(*sockfd, IPPROTO_IP, IP_HDRINCL, &(int){1}, sizeof(int))
                   == -1)
    {
        dprintf(STDERR_FILENO, "ft_nmap: setsockopt(): %s", strerror(errno));
        return (FAILURE);
    }
    return (SUCCESS);
}

uint8_t         setup_sockfd(t_thread *thread, uint8_t scan)
{
    if (scan & SCAN_SYN)
    {
        if (socket_handler((struct sockaddr_in *)&(thread->dst),
                            &thread->sockets[S_SYN], IPPROTO_TCP) != SUCCESS)
            return (FAILURE);
    }
    if (scan & SCAN_ACK)
    {
        if (socket_handler((struct sockaddr_in *)&(thread->dst),
                            &thread->sockets[S_ACK], IPPROTO_TCP) != SUCCESS)
            return (FAILURE);
    }
    if (scan & SCAN_FIN)
    {
        if (socket_handler((struct sockaddr_in *)&(thread->dst),
                            &thread->sockets[S_FIN], IPPROTO_TCP) != SUCCESS)
            return (FAILURE);
    }
    if (scan & SCAN_XMAS)
    {
        if (socket_handler((struct sockaddr_in *)&(thread->dst),
                            &thread->sockets[S_XMAS], IPPROTO_TCP) != SUCCESS)
            return (FAILURE);
    }
    if (scan & SCAN_NULL)
    {
        if (socket_handler((struct sockaddr_in *)&(thread->dst),
                            &thread->sockets[S_NULL], IPPROTO_TCP) != SUCCESS)
            return (FAILURE);
    }
    if (scan & SCAN_UDP)
    {
        if (socket_handler((struct sockaddr_in *)&(thread->dst),
                            &thread->sockets[S_UDP], IPPROTO_UDP) != SUCCESS)
            return (FAILURE);
        if (socket_handler((struct sockaddr_in *)&(thread->dst),
                            &thread->sockets[S_UDP_ICMP_RESPONSE],
                            IPPROTO_ICMP) != SUCCESS)
            return (FAILURE);
    }
    return (SUCCESS);
}
