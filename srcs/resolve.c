/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 13:11:04 by arsciand          #+#    #+#             */
/*   Updated: 2021/07/09 20:16:46 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

uint8_t     resolve_target_ipv4(t_nmap *nmap, char *arg)
{
    struct  addrinfo    hints;
    struct  addrinfo    *res    = NULL;
    int                 status  = 0;

    ft_bzero(&hints, sizeof(struct addrinfo));

    hints.ai_flags      = AI_V4MAPPED | AI_ADDRCONFIG;
    hints.ai_family     = AF_INET;
    hints.ai_socktype   = 0;

    /**/
    #pragma clang diagnostic ignored "-Wcast-align"
    /**/

    if ((status = getaddrinfo(arg, NULL, &hints, &res)) != SUCCESS)
    {
        getaddrinfo_error_handler(arg, status);
        return (FAILURE);
    }

    ((struct sockaddr_in *)&nmap->target)->sin_addr.s_addr
        = ((struct sockaddr_in*)res->ai_addr)->sin_addr.s_addr;
    ((struct sockaddr_in *)&nmap->target)->sin_family
        = (sa_family_t)res->ai_family;

    for (struct addrinfo *tmp = NULL; res; res = tmp)
    {
        tmp = res->ai_next;
        free(res);
    }

    return (SUCCESS);
}

    ((struct sockaddr_in *)&nmap->target)->sin_addr.s_addr = ((struct sockaddr_in*)res->ai_addr)->sin_addr.s_addr;
    ((struct sockaddr_in *)&nmap->target)->sin_family      = (sa_family_t)res->ai_family;

    for (struct addrinfo *tmp = NULL; res; res = tmp)
    {
        tmp = res->ai_next;
        free(res);
    }

    return (SUCCESS);
}
