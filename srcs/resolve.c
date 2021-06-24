/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 13:11:04 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/24 19:51:21 by arsciand         ###   ########.fr       */
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

    if (!(inet_ntop(res->ai_family, &(((struct sockaddr_in *)res->ai_addr)->sin_addr), nmap->target_ipv4,
        sizeof(nmap->target_ipv4))))
        {
            return (FAILURE);
        }

    for (struct addrinfo *tmp = NULL; res; res = tmp)
    {
        tmp = res->ai_next;
        free(res);
    }

    return (SUCCESS);
}
