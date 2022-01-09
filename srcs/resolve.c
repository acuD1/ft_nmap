/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 13:11:04 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/07 13:41:47 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

uint8_t     resolve_target_ipv4(t_target *target, char *arg)
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

    ((struct sockaddr_in *)&target->dst)->sin_addr.s_addr
        = ((struct sockaddr_in*)res->ai_addr)->sin_addr.s_addr;
    ((struct sockaddr_in *)&target->dst)->sin_family
        = (sa_family_t)res->ai_family;

    for (struct addrinfo *tmp = NULL; res; res = tmp)
    {
        tmp = res->ai_next;
        free(res);
    }

    return (SUCCESS);
}

uint8_t     resolve_local_ipv4(t_target *target)
{
    struct ifaddrs  *ifap   = NULL;

    if (getifaddrs(&ifap) == -1)
    {
        dprintf(STDERR_FILENO, "ft_nmap: getifaddrs(): %s\n", strerror(errno));
        return (FAILURE);
    }


    if (is_loopback((struct sockaddr_in *)&target->dst) == SUCCESS)
    {
        for (struct ifaddrs *ifa = ifap; ifa; ifa = ifa->ifa_next)
        {
            if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET
                && (ifa->ifa_flags & (IFF_LOOPBACK))
                && (ifa->ifa_flags & (IFF_RUNNING)))
            {
                ((struct sockaddr_in *)&target->src)->sin_addr
                    = ((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
                if (!(target->device= ft_strdup(ifa->ifa_name)))
                    return (FAILURE);
            }
        }
    }
    else
    {
        for (struct ifaddrs *ifa = ifap; ifa; ifa = ifa->ifa_next)
        {
            if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET
                && !(ifa->ifa_flags & (IFF_LOOPBACK))
                && (ifa->ifa_flags & (IFF_RUNNING)))
            {
                ((struct sockaddr_in *)&target->src)->sin_addr
                    = ((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
                if (!(target->device = ft_strdup(ifa->ifa_name)))
                    return (FAILURE);
            }
        }
    }
    freeifaddrs(ifap);
    return (SUCCESS);
}
