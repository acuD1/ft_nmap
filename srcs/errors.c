/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 13:15:56 by arsciand          #+#    #+#             */
/*   Updated: 2021/07/16 14:45:03 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void     getaddrinfo_error_handler(char *arg, int status)
{
    switch (status)
    {
        case EAI_ADDRFAMILY:
            dprintf(STDERR_FILENO,
                "ft_nmap: %s: Address family for hostname not supported\n",
                arg);
            break ;
        case EAI_AGAIN:
            dprintf(STDERR_FILENO,
                "ft_nmap: %s: Temporary failure in name resolution\n",
                arg);
            break ;
        case EAI_NODATA:
            dprintf(STDERR_FILENO,
                "ft_nmap: %s: No address associated with hostname\n",
                arg);
            break ;
        case EAI_NONAME:
            dprintf(STDERR_FILENO,
                "ft_nmap: %s: Name or service not known\n",
                arg);
            break ;
        case EAI_SYSTEM:
            dprintf(STDERR_FILENO,
                "ft_nmap: %s: System error\n",
                arg);
            break ;
    }
}
