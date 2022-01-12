/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:30:22 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/12 18:22:40 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include "str.h"

void        print_usage(void)
{
    dprintf(STDOUT_FILENO, "%s%s%s%s",
            "ft_nmap [--help] [--dry-run]\n",
            "\t[--ip [ADRESSE]] [--ports [NOMBRE/PLAGE]] ",
            "[--scan [TYPE]] [--speedup [NOMBRE]] \n",
            "\t[--file [FICHIER]] [--scan [TYPE]] [--speedup [NOMBRE]]\n");
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
    t_result    *result     = (t_result *)data;
    uint8_t     first       = 0;
    uint8_t address_len     = 16;
    uint8_t spacing         = address_len + 30;
    char        *address
                    = inet_ntoa(((struct sockaddr_in *)&result->dst)->sin_addr);

    dprintf(STDOUT_FILENO, "%-*s  %-8d  %-16s  ", address_len, address,
            result->port, services_tcp(result->port)
                            ? services_tcp(result->port)
                            : services_udp(result->port));

    if (result->scan & SCAN_SYN)
    {
        if (first == 0)
            first = 1;
        else
            dprintf(STDOUT_FILENO, "%20s", "");
        dprintf(STDOUT_FILENO, "SYN  -> %s\n",
                port_status(result->status[S_SYN]));
    }
    if (result->scan & SCAN_ACK)
    {
        if (first == 0)
            first = 1;
        else
            dprintf(STDOUT_FILENO, "%*s", spacing,  "");
        dprintf(STDOUT_FILENO, "ACK  -> %s\n",
                port_status(result->status[S_ACK]));
    }
    if (result->scan & SCAN_FIN)
    {
        if (first == 0)
            first = 1;
        else
            dprintf(STDOUT_FILENO, "%*s", spacing,  "");
        dprintf(STDOUT_FILENO, "FIN  -> %s\n",
                port_status(result->status[S_FIN]));
    }
    if (result->scan & SCAN_XMAS)
    {
        if (first == 0)
            first = 1;
        else
            dprintf(STDOUT_FILENO, "%*s", spacing,  "");
        dprintf(STDOUT_FILENO, "XMAS -> %s\n",
                port_status(result->status[S_XMAS]));
    }
    if (result->scan & SCAN_NULL)
    {
        if (first == 0)
            first = 1;
        else
            dprintf(STDOUT_FILENO, "%*s", spacing,  "");
        dprintf(STDOUT_FILENO, "NULL -> %s\n",
                port_status(result->status[S_NULL]));
    }
    if (result->scan & SCAN_UDP)
    {
        if (first == 0)
            first = 1;
        else
            dprintf(STDOUT_FILENO, "%*s", spacing,  "");
        dprintf(STDOUT_FILENO, "UDP  -> %s\n",
                port_status(result->status[S_UDP]));
    }
}
