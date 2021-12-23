/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:42:49 by arsciand          #+#    #+#             */
/*   Updated: 2021/12/23 15:52:39 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

const char   *debug_scan(t_scan_type scan)
{
    switch (scan)
    {
        case S_SYN:
            return ("SYN");
        case S_FIN:
            return ("FIN");
        case S_ACK:
            return ("ACK");
        case S_XMAS:
            return ("XMAS");
        case S_NULL:
            return ("NULL");
        case S_UDP:
            return ("UDP");
    }
}
