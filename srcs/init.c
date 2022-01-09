/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:09:07 by cempassi          #+#    #+#             */
/*   Updated: 2022/01/09 11:46:54 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

// t_nmap_global   g_nmap;

static void set_defaults(t_nmap *nmap)
{
    // Init nmap
    ft_bzero(nmap, sizeof(t_nmap));
    nmap->threads      = DEFAULT_THREADS;
}

void        init_nmap(t_nmap *nmap, int argc, char **argv)
{
    setbuf(stdout, NULL);
    set_defaults(nmap);

    // if (pthread_mutex_init(&(g_nmap.lock), NULL) != 0)
    // {
    //     dprintf(STDERR_FILENO, "ft_nmap: init_map(): Mutex init failed\n");
    //     exit_routine(nmap, FAILURE);
    // }

    if (set_opts_args(nmap, argc, argv) != SUCCESS)
        exit_routine(nmap, FAILURE);
}
