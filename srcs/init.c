/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:09:07 by cempassi          #+#    #+#             */
/*   Updated: 2021/12/23 16:12:14 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

t_nmap_global   *g_nmap = NULL;

static void set_defaults(t_nmap *nmap)
{
    if (!(g_nmap = ft_memalloc(sizeof(t_nmap_global))))
        exit_routine(nmap, FAILURE);
    g_nmap->src_port    = DEFAULT_SRC_PORT;
    g_nmap->seq         = DEFAULT_SEQ;
    ft_bzero(nmap, sizeof(t_nmap));
    nmap->threads = DEFAULT_THREADS;
}

void        init_nmap(t_nmap *nmap, int argc, char **argv)
{
    setbuf(stdout, NULL);
    set_defaults(nmap);
    if (pthread_mutex_init(&g_nmap->lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        exit_routine(nmap, FAILURE);
    }

    if (set_opts_args(nmap, argc, argv) != SUCCESS)
        exit_routine(nmap, FAILURE);
    if (resolve_local_ipv4(nmap) != SUCCESS)
        exit_routine(nmap, FAILURE);
}
