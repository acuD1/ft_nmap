/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 12:30:31 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/09 18:44:04 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void    exec_nmap(t_nmap *nmap)
{
    if (getuid() != 0)
    {
        dprintf(STDERR_FILENO, "ft_nmap: socket: Operation not permitted\n");
        exit_routine(nmap, FAILURE);
    }

    for (t_list *target = nmap->targets; target; target = target->next)
    {

        if (g_nmap.is_canceld == TRUE)
            exit_routine(nmap, FAILURE);
            
        #ifdef DEBUG
            debug_source_ip(target->data);
        #endif

        if (scan_target(target->data, nmap) == FAILURE)
        {
            dprintf(STDERR_FILENO,
                "ft_nmap: scan_target(): An error has occured\n");
            exit_routine(nmap, EXIT_FAILURE);
        }
    }
}
