/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 12:30:31 by arsciand          #+#    #+#             */
/*   Updated: 2021/07/26 16:01:44 by cempassi         ###   ########.fr       */
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

void    exec_nmap(t_nmap *nmap)
{
    dprintf(STDOUT_FILENO, "[DEBUG] SOURCE IP\t\t\t-> |%s|\n",
        inet_ntoa(((struct sockaddr_in *)&nmap->local)->sin_addr));
    ft_lstiter(nmap->target, print_target);

    ft_lstiter_ctx(nmap->target, nmap, send_target);
}
