/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:30:22 by arsciand          #+#    #+#             */
/*   Updated: 2021/12/15 22:53:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void print_usage(void)
{
    dprintf(STDOUT_FILENO, "%s%s",
            "ft_nmap [--help] [--ports [NOMBRE/PLAGE]] [--dry-run] ",
            "[--speedup [NOMBRE]] [--scan [TYPE]] --ip [ADRESSE]\n");
}

void print_source_ip(t_nmap *nmap)
{
    dprintf(STDOUT_FILENO, "[DEBUG] SOURCE IP\t\t\t-> |%s|\n",
            inet_ntoa(((struct sockaddr_in *)&nmap->local)->sin_addr));
}

void print_unallowed_opt(t_opts_args *opts_args)
{
    if (opts_args->invalid)
        fprintf(stderr, "ft_nmap: unrecognized option '--%s'\n",
                opts_args->invalid);
    else
        fprintf(stderr, "ft_nmap: invalid option -- '%c'\n",
                (char)(opts_args->all % 128));
    free_opts_args(opts_args);
}

void print_requires_arg_opt_long(char *current)
{
    dprintf(STDERR_FILENO, "%s%s%s\n%s\n", "ft_nmap: option '--", current,
            "' requires an argument",
            "See the output of ft_nmap --help for a summary of options.");
}

void print_target(void *data)
{
    t_target *target;

    target = data;
    dprintf(STDOUT_FILENO, "[DEBUG] TARGET IP\t\t\t-> |%s|\n",
       inet_ntoa(((struct sockaddr_in *)&target->dest)->sin_addr));
    ft_lstiter(target->ports, display_token);
}

void display_token(void *data)
{
    t_port *port;

    port = data;
    printf("-------------\n");
    if (port->type == E_PORT_UNSET)
    {
        printf("TYPE: UNSET\n");
    }
    else if (port->type == E_PORT_SINGLE)
    {
        printf("TYPE: SINGLE\nDATA: %d\n", port->data.port);
    }
    else
    {
        printf("TYPE: RANGE\nDATA: [%d - %d]\n", port->data.range[0],
               port->data.range[1]);
    }
    printf("-------------\n");
}

void debug_ports(t_list *ports)
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
