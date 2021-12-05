/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:09:07 by cempassi          #+#    #+#             */
/*   Updated: 2021/08/22 13:44:41 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include <unistd.h>
#include <sys/types.h>


static void set_defaults(t_nmap *nmap)
{
    ft_bzero(nmap, sizeof(t_nmap));
    nmap->threads = NULL;
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
    ft_lstiter(nmap->targets, print_target);
}
