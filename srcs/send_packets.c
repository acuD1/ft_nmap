/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_packets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 12:29:50 by arsciand          #+#    #+#             */
/*   Updated: 2021/07/11 17:57:14 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void setup_ipv4_sockaddr_in(
            struct sockaddr_in *setup, struct sockaddr_storage *type)
{
    ft_bzero(setup, sizeof(struct sockaddr_in));
    ft_memcpy(setup,  (struct sockaddr_in *)type, sizeof(struct sockaddr_in));
}

static void setup_sockfd(t_nmap *nmap, struct sockaddr_in *dest, int *sockfd)
{
    if ((*sockfd = socket(dest->sin_family, SOCK_RAW, IPPROTO_TCP)) == -1)
    {
        printf("[DEBUG] socket(): ERROR: %s , errno %d\n", strerror(errno), errno);
        exit_routine(nmap, FAILURE);
    }
}

static void setup_th_flags(t_nmap *nmap, t_packet *packet)
{
    if (nmap->scan & SCAN_SYN)
        packet->tcphdr.th_flags = TH_SYN;
    if (nmap->scan & SCAN_FIN)
        packet->tcphdr.th_flags = TH_FIN;
    if (nmap->scan & SCAN_ACK)
        packet->tcphdr.th_flags = TH_ACK;
    if (nmap->scan & SCAN_XMAS)
    {
        packet->tcphdr.th_flags |= TH_FIN;
        packet->tcphdr.th_flags |= TH_PUSH;
        packet->tcphdr.th_flags |= TH_URG;
    }
    if (nmap->scan & SCAN_NULL)
        packet->tcphdr.th_flags = 0;
    if (nmap->scan & DEFAULT_SCAN)
    {
        dprintf(STDERR_FILENO, "[NOT IMPLEMENTED] Multi scans\n");
        exit_routine(nmap, FAILURE);
    }
}

static void setup_packet(
        t_nmap *nmap, t_packet *packet, struct sockaddr_in *src,
        struct sockaddr_in *dest)
{
    static uint32_t static_seq  = 420000;

    ft_bzero(packet, sizeof(t_packet));

    /* Pseudo Header */
	packet->saddr            = src->sin_addr.s_addr;
	packet->daddr            = dest->sin_addr.s_addr;
	packet->protocol         = IPPROTO_TCP;
	packet->tcp_len          = htons(sizeof(struct tcphdr));

	/* TCP Header */
	packet->tcphdr.th_sport  = src->sin_port;
	packet->tcphdr.th_dport  = dest->sin_port;
	packet->tcphdr.th_seq    = htonl(static_seq++);
	packet->tcphdr.th_off    = sizeof(struct tcphdr) / 4;

    setup_th_flags(nmap, packet);

	packet->tcphdr.th_win    = htons(1024);
	packet->tcphdr.th_sum    = in_cksum(packet, sizeof(t_packet));
}

static void TEST_send_SYN_or_FIN(t_nmap *nmap, int sockfd, struct sockaddr_in *src,
            struct sockaddr_in *dest)
{
    ssize_t     bytes_sent  = 0;
    t_packet    packet;

    setup_packet(nmap, &packet, src, dest);

    if ((bytes_sent = sendto(sockfd, &packet.tcphdr, sizeof(struct tcphdr), 0,
                        (struct sockaddr *)dest, sizeof(struct sockaddr))) == -1)
    {
        printf("[DEBUG] sendto(): ERROR: %s , errno %d\n", strerror(errno), errno);
        exit_routine(nmap, FAILURE);
    }
    printf("[DEBUG] BYTES_SENT \t\t\t-> |%zd|\n", bytes_sent);
}

void        send_packets(t_nmap *nmap)
{
    struct sockaddr_in  dest;
	struct sockaddr_in  src;
    int                 sockfd          =  0;

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

        TEST_send_SYN_or_FIN(nmap, sockfd, &src, &dest);
    }
}
