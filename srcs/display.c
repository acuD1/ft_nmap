/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:30:22 by arsciand          #+#    #+#             */
/*   Updated: 2021/12/19 14:27:02 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include "list.h"

void print_usage(void)
{
    dprintf(STDOUT_FILENO, "%s%s",
            "ft_nmap [--help] [--ports [NOMBRE/PLAGE]] [--dry-run] ",
            "[--speedup [NOMBRE]] [--scan [TYPE]] --ip [ADRESSE]\n");
}

void        print_unallowed_opt(t_opts_args *opts_args)
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

    dprintf(STDOUT_FILENO, "[DEBUG] --------- PRINTING TARGET ---------\t\t\t\n");
    dprintf(STDOUT_FILENO, "[DEBUG] TARGET DEST\t\t\t-> |%s|\n",
       inet_ntoa(((struct sockaddr_in *)&target->dst)->sin_addr));
    dprintf(STDOUT_FILENO, "[DEBUG] TARGET PORT NBR\t\t\t-> |%u|\n",
       target->port_nbr);
    dprintf(STDOUT_FILENO, "[DEBUG] TARGET PORT PER THREAD\t\t-> |%u|\n",
       target->port_per_thread);
    dprintf(STDOUT_FILENO, "[DEBUG] TARGET PORT LEFTOVER\t\t-> |%u|\n",
       target->port_leftover);
    ft_lstiter(target->ports, print_token);
}

static void print_port(void *data)
{
    u_int16_t *port;

    port = data;
    dprintf(STDOUT_FILENO, "[DEBUG] PORT %u\t\t\t\n", *port);
}

void print_thread(void *data)
{
    t_thread *thread;

    thread = data;
    dprintf(STDOUT_FILENO, "[DEBUG] --------- PRINTING THREAD ---------\t\t\t\n");
    dprintf(STDOUT_FILENO, "[DEBUG] --------- PRINTING PORT ---------\t\t\t\n");
    ft_lstiter(thread->ports, print_port);
}

void print_token(void *data)
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


