/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portscan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:27:15 by cempassi          #+#    #+#             */
/*   Updated: 2021/12/16 01:52:47 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include "list.h"
#include <strings.h>

// - scan_thread
//  - scan_thread
//    - scan_port

t_list *generate_threads(t_list *target_ports, uint8_t port_per_thread)
{
    t_list    *threads;
    t_thread  thread;
    uint8_t   port_nbr = 0;
    t_list    *single_port;
    t_list    *new_thread;

    threads = NULL;

    bzero(&thread, sizeof(t_thread));
    for (t_list *current = target_ports; current == NULL ; current = current->next)
    {
        t_port *target_port = current->data;
        if (target_port->type == E_PORT_SINGLE) {
            port_nbr++;
            single_port = ft_lstnew(&target_port->data.port, sizeof(uint16_t));
            ft_lstaddback(&thread.ports, single_port);
        }

        if (port_nbr == port_per_thread) {
            new_thread = ft_lstnew(&thread, sizeof(t_thread));
            ft_lstaddback(&threads, new_thread);
            bzero(&thread, sizeof(t_thread));
            port_nbr = 0;
        }
    }

    return (threads);
}
int scan_target(void *data, void *context)
{
    t_target *target;
    t_nmap *  nmap;
    t_list *  threads;

    nmap = context;
    target = data;
    threads = NULL;
    print_target(target);

    printf("Scanning target\n");

    // Thread repartition must happend here
    // port_per_thread =
    // target + port_per_thread = list of threads
    return (SUCCESS);
}
