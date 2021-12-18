/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 12:30:31 by arsciand          #+#    #+#             */
/*   Updated: 2021/12/18 17:23:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include <stdio.h>

void exec_nmap(t_nmap *nmap)
{
    if (getuid() != 0)
    {
        dprintf(STDERR_FILENO, "ft_nmap: socket: Operation not permitted\n");
        exit_routine(nmap, FAILURE);
    }

    /* Display information */
    print_source_ip(nmap);

    /* Portscan */
    // if (nmap->options)
    /* The return has to be controlled here  */
    for (t_list *target = nmap->targets; target; target = target->next)
    {
        if(scan_target(target->data, nmap) == FAILURE)
        {
            dprintf(STDERR_FILENO, "[ERROR] on scan target\n");
        }
    }
}
