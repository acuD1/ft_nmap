/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 12:30:31 by arsciand          #+#    #+#             */
/*   Updated: 2021/08/08 12:55:34 by cempassi         ###   ########.fr       */
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


    if (nmap->options)
    ft_lstiter_ctx(nmap->target, nmap, send_target);
}
