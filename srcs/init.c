/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:09:07 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/25 17:38:30 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void set_defaults(t_nmap *nmap)
{
    ft_bzero(nmap, sizeof(t_nmap));
    ft_bzero(&nmap->target_ipv4, sizeof(nmap->target_ipv4));
    nmap->threads = DEFAULT_THREADS;
    nmap->scan = DEFAULT_SCAN;
    nmap->ports = NULL;
}

uint8_t     init_nmap(t_nmap *nmap, int argc, char **argv)
{
    set_defaults(nmap);
    if (set_opts_args(nmap, argc, argv) != SUCCESS)
        exit_routine(nmap, FAILURE);
    return (SUCCESS);
}
