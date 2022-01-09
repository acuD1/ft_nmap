/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:42:49 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/09 09:33:59 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

#ifdef DEBUG
void                debug_bytes(int bytes, void *msg)
{
    for (int i = 0; i < bytes; i++)
    {
        if (!(i & 15))
            printf("\n[DEBUG] %04X:  ", i);
        printf("%02X ", ((unsigned char*)msg)[i]);
    }
    printf("\n");
}

const char          *debug_scan(t_scan_type scan)
{
    switch (scan)
    {
        case S_SYN:
            return ("SYN");
        case S_FIN:
            return ("FIN");
        case S_ACK:
            return ("ACK");
        case S_XMAS:
            return ("XMAS");
        case S_NULL:
            return ("NULL");
        case S_UDP:
            return ("UDP");
    }
}

void                debug_source_ip(t_target *target)
{
    dprintf(STDOUT_FILENO, "[DEBUG] SOURCE IP\t\t\t-> |%s| on |%s|\n",
            inet_ntoa(((struct sockaddr_in *)&target->src)->sin_addr),
            target->device);
}

static void         debug_token(void *data)
{
    t_port *port;

    port = data;
    dprintf(STDERR_FILENO, "-------------\n");
    if (port->type == E_PORT_UNSET)
        dprintf(STDERR_FILENO, "TYPE: UNSET\n");
    else if (port->type == E_PORT_SINGLE)
        dprintf(STDERR_FILENO, "TYPE: SINGLE\nDATA: %d\n", port->data.port);
    else
        dprintf(STDERR_FILENO, "TYPE: RANGE\nDATA: [%d - %d]\n",
                port->data.range[0], port->data.range[1]);
    dprintf(STDERR_FILENO, "-------------\n");
}

void                debug_target(void *data)
{
    t_target *target;

    target = data;

    dprintf(STDOUT_FILENO,
            "[DEBUG] --------- PRINTING TARGET ---------\t\t\t\n");
    dprintf(STDOUT_FILENO, "[DEBUG] TARGET DEST\t\t\t-> |%s|\n",
       inet_ntoa(((struct sockaddr_in *)&target->dst)->sin_addr));
    dprintf(STDOUT_FILENO, "[DEBUG] TARGET PORT NBR\t\t\t-> |%u|\n",
       target->port_nbr);
    dprintf(STDOUT_FILENO, "[DEBUG] TARGET PORT PER THREAD\t\t-> |%u|\n",
       target->port_per_thread);
    dprintf(STDOUT_FILENO, "[DEBUG] TARGET PORT LEFTOVER\t\t-> |%u|\n",
       target->port_leftover);
    ft_lstiter(target->ports, debug_token);
}

void               debug_ports(t_list *ports)
{
    t_list *tmp_ports = ports;
    t_port *tmp_port = NULL;

    while (tmp_ports)
    {
        tmp_port = (t_port *)tmp_ports->data;
        if (tmp_port->type == E_PORT_SINGLE)
            dprintf(STDERR_FILENO, "[DEBUG]\t\t\tE_PORT_SINGLE\t-> |%d|\n",
                    tmp_port->data.port);
        if (tmp_port->type == E_PORT_RANGE)
            dprintf(STDERR_FILENO, "[DEBUG]\t\t\tE_PORT_RANGE\t-> |%d|-|%d|\n",
                    tmp_port->data.range[0], tmp_port->data.range[1]);
        tmp_ports = tmp_ports->next;
    }
}

#endif
