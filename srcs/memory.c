/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 18:43:16 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/08 16:21:30 by arsciand         ###   ########.fr       */
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
}

void                            free_nmap(t_nmap *nmap)
{
    ft_lstdel(&nmap->targets, del_target);
}
