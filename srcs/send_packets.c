/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_packets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 12:29:50 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/26 12:50:00 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void    setup_ipv4_sockaddr_in(
            struct sockaddr_in *setup, struct sockaddr_storage *type)
{
    ft_bzero(setup, sizeof(struct sockaddr_in));
    ft_memcpy(setup,  (struct sockaddr_in *)type, sizeof(struct sockaddr_in));
}

void    setup_sockfd(t_nmap *nmap, struct sockaddr_in *dest, int *sockfd)
{
    if ((*sockfd = socket(dest->sin_family, SOCK_RAW, IPPROTO_TCP)) == -1)
    {
        printf("[DEBUG] socket(): ERROR: %s , errno %d\n", strerror(errno), errno);
        exit_routine(nmap, FAILURE);
    }
}
void    send_packets(t_nmap *nmap)
{
    struct sockaddr_in  dest;
	struct sockaddr_in  src;
    int                 sockfd        =  0;

    /* TMP */
    uint16_t            tmp_range[2]    = {440, 443};
    uint16_t            tmp_s_port      = 33000;

    setup_ipv4_sockaddr_in(&src, &nmap->local);
    setup_ipv4_sockaddr_in(&dest, &nmap->target);


    for (uint16_t d_port = tmp_range[0]; d_port <= tmp_range[1]; d_port++)
    {
        setup_sockfd(nmap, &dest, &sockfd);

        dest.sin_port = htons(d_port);
        src.sin_port = htons(tmp_s_port++);

    }
}
