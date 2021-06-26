/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 12:30:31 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/26 12:54:21 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void    exec_nmap(t_nmap *nmap)
{
    dprintf(STDOUT_FILENO, "[DEBUG]\nIP  : |%s|\n", nmap->target_ipv4);

    if (nmap->scan & SCAN_SYN)
        test_send_SYN(nmap);
}
