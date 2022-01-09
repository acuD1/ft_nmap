/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:30:22 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/09 10:02:51 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void        print_usage(void)
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

void        print_requires_arg_opt_long(char *current)
{
    dprintf(STDERR_FILENO, "%s%s%s\n%s\n", "ft_nmap: option '--", current,
            "' requires an argument",
            "See the output of ft_nmap --help for a summary of options.");
}

static const char   *port_status(t_port_status port_status)
{
    switch (port_status)
    {
        case E_OPEN:
            return ("OPEN");
        case E_CLOSED:
            return ("CLOSED");
        case E_FILTERED:
            return ("FILTERED");
        case E_OPEN_FILTERED:
            return ("OPEN_FILTERED");
        case E_UNFILTERED:
            return ("UNFILTERED");
    }
}

void                display_results(void *data)
{
    t_result *result = (t_result *)data;

    dprintf(STDOUT_FILENO, "%s:%d\n",
            inet_ntoa(((struct sockaddr_in *)&result->dst)->sin_addr),
            result->port);

    if (result->scan & SCAN_SYN)
        dprintf(STDOUT_FILENO, "\t\t\t- SYN  -> %s\n",
                port_status(result->status[S_SYN]));
    if (result->scan & SCAN_ACK)
        dprintf(STDOUT_FILENO, "\t\t\t- ACK  -> %s\n",
                port_status(result->status[S_ACK]));
    if (result->scan & SCAN_FIN)
        dprintf(STDOUT_FILENO, "\t\t\t- FIN  -> %s\n",
                port_status(result->status[S_FIN]));
    if (result->scan & SCAN_XMAS)
        dprintf(STDOUT_FILENO, "\t\t\t- XMAS -> %s\n",
                port_status(result->status[S_XMAS]));
    if (result->scan & SCAN_NULL)
        dprintf(STDOUT_FILENO, "\t\t\t- NULL -> %s\n",
                port_status(result->status[S_NULL]));
    if (result->scan & SCAN_UDP)
        dprintf(STDOUT_FILENO, "\t\t\t- UDP  -> %s\n",
                port_status(result->status[S_UDP]));
}


