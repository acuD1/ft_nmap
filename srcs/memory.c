/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 18:43:16 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/11 10:45:44 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void __attribute__ ((noreturn)) exit_routine(t_nmap *nmap, uint8_t status)
{
    free_nmap(nmap);
    exit(status);
}

static void                     del_target(void *data)
{
    t_target *target;

    target = data;
    ft_lstdel(&target->ports, NULL);
    ft_strdel(&target->device);
}

void delete_thread(void *data)
{
    t_thread *thread;

    thread = data;

    ft_strdel(&thread->filter.buffer);
    ft_lstdel(&thread->results, NULL);
    if (thread->sniffer)
        pcap_close(thread->sniffer);
    thread->sniffer = NULL;
    if (thread->compiled_filter.bf_insns)
        free(thread->compiled_filter.bf_insns);
    ft_bzero(&thread->compiled_filter, sizeof(thread->compiled_filter));
}

void                            free_nmap(t_nmap *nmap)
{
    ft_lstdel(&nmap->targets, del_target);
}
