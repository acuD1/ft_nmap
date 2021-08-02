/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:09:07 by cempassi          #+#    #+#             */
/*   Updated: 2021/08/02 10:04:12 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void    print_target(void *data)
{
    t_target *target;

    target = data;
    dprintf(STDOUT_FILENO, "[DEBUG] TARGET IP\t\t\t-> |%s|\n",
       inet_ntoa(((struct sockaddr_in *)&target->target)->sin_addr));
    ft_lstiter(target->ports, display_token);
}

static void set_defaults(t_nmap *nmap)
{
    ft_bzero(nmap, sizeof(t_nmap));
    nmap->threads = DEFAULT_THREADS;
    nmap->target = NULL;
    // nmap->scan = DEFAULT_SCAN; // Temporay fix
}

void     init_nmap(t_nmap *nmap, int argc, char **argv)
{
    set_defaults(nmap);
    if (set_opts_args(nmap, argc, argv) != SUCCESS)
        exit_routine(nmap, FAILURE);
    if (resolve_local_ipv4(nmap) != SUCCESS)
        exit_routine(nmap, FAILURE);
    dprintf(STDOUT_FILENO, "[DEBUG] SOURCE IP\t\t\t-> |%s|\n",
        inet_ntoa(((struct sockaddr_in *)&nmap->local)->sin_addr));
    ft_lstiter(nmap->target, print_target);
}
