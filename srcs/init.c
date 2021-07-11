/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:09:07 by cempassi          #+#    #+#             */
/*   Updated: 2021/07/09 16:52:03 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void set_defaults(t_nmap *nmap)
{
    ft_bzero(nmap, sizeof(t_nmap));
    nmap->threads = DEFAULT_THREADS;
    nmap->scan = DEFAULT_SCAN;
    nmap->ports = NULL;
}

void     init_nmap(t_nmap *nmap, int argc, char **argv)
{
    set_defaults(nmap);
    if (set_opts_args(nmap, argc, argv) != SUCCESS)
        exit_routine(nmap, FAILURE);
    if (resolve_local_ipv4(nmap) != SUCCESS)
        exit_routine(nmap, FAILURE);
}
