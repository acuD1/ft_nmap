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
void    send_packets(t_nmap *nmap)
{
    struct sockaddr_in  dest;
	struct sockaddr_in  src;

    setup_ipv4_sockaddr_in(&src, &nmap->local);
    setup_ipv4_sockaddr_in(&dest, &nmap->target);


}
