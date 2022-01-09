/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_filter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 11:27:09 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/09 09:39:59 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include "vector.h"
#include <stdio.h>

uint8_t generate_filter_tcp_udp(t_thread *thread)
{
    if (thread->scan & SCAN_UDP && is_tcp_scan(thread->scan))
        return (SUCCESS);

    if (thread->scan & SCAN_UDP)
    {
        if (vct_insert_string(&thread->filter, "udp", 0) != SUCCESS)
        {
            dprintf(STDERR_FILENO,
                    "ft_nmap: vct_insert_string():  Malloc error\n");
            return (FAILURE);
        }
    }
    else
    {
        if (vct_insert_string(&thread->filter, "tcp", 0) != SUCCESS)
        {
            dprintf(STDERR_FILENO,
                    "ft_nmap: vct_insert_string():  Malloc error\n");
            return (FAILURE);
        }
    }
    return (SUCCESS);
}

uint8_t generate_filter_icmp(t_thread *thread)
{
    if (thread->scan & SCAN_UDP)
    {
        if (vct_insert_string(&thread->filter, " or icmp", 0) != SUCCESS)
        {
            dprintf(STDERR_FILENO,
                    "ft_nmap: vct_insert_string():  Malloc error\n");
            return (FAILURE);
        }
    }
    return (SUCCESS);
}

uint8_t generate_filter_port_single(t_thread *thread, uint16_t port)
{
    char buffer[13];

    ft_bzero(buffer, 13);

    snprintf(buffer, 12, " port %d", port);

    if (vct_insert_string(&thread->filter, buffer, 0) != SUCCESS)
    {
        dprintf(STDERR_FILENO,
                "ft_nmap: vct_insert_string(): Malloc error\n");
        return (FAILURE);
    }
    return (SUCCESS);
}

uint8_t generate_filter_port_range(t_thread *thread, uint16_t start,
                                    uint16_t end)
{
    char buffer[24];

    ft_bzero(buffer, 24);

    snprintf(buffer, 23, " portrange %d-%d", start, end);

    if (vct_insert_string(&thread->filter, buffer, 0) != SUCCESS)
    {
        dprintf(STDERR_FILENO, "ft_nmap: vct_insert_string(): Malloc error\n");
        return (FAILURE);
    }
    return (SUCCESS);
}

uint8_t generate_filter_src(t_list *threads)
{
    char buffer[25];

    for (t_list *tmp = threads; tmp; tmp = tmp->next)
    {
        t_thread    *thread = (t_thread *)tmp->data;
        char        *src    = NULL;

        if (!(((struct sockaddr_in *)&thread->dst)->sin_addr.s_addr))
            src = "127.0.0.1";
        else
        {
            src = inet_ntoa(((struct sockaddr_in *)&thread->dst)->sin_addr);
            if (src == NULL)
                return (FAILURE);
        }

        snprintf(buffer, 24, " and src %s", src);

        if (vct_insert_string(&thread->filter, buffer, 0) != SUCCESS)
        {
            dprintf(STDERR_FILENO, "ft_nmap: vct_insert_string(): Malloc error\n");
            return (FAILURE);
        }
    }
    return (SUCCESS);
}

uint8_t generator_filter_or(t_thread *thread)
{
    if (vct_insert_string(&thread->filter, " or", 0) != SUCCESS)
    {
        dprintf(STDERR_FILENO, "ft_nmap: vct_insert_string(): Malloc error\n");
        return (FAILURE);
    }
    return (SUCCESS);
}

