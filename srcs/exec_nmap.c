/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 12:30:31 by arsciand          #+#    #+#             */
/*   Updated: 2021/07/09 19:24:55 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void    exec_nmap(t_nmap *nmap)
{
    dprintf(STDOUT_FILENO, "[DEBUG] SOURCE IP\t\t\t-> |%s|\n",
        inet_ntoa(((struct sockaddr_in *)&nmap->local)->sin_addr));

    if (nmap->scan & SCAN_SYN)
        test_send_SYN(nmap);
}
