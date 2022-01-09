/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_tcp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:42:59 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/09 11:48:20 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void setup_th_flags(t_tcp_packet *template, t_scan_type scan)
{
    switch (scan)
    {
        case S_SYN:
            template->tcpheader.th_flags = TH_SYN;
            break ;
        case S_FIN:
            template->tcpheader.th_flags = TH_FIN;
            break ;
        case S_ACK:
            template->tcpheader.th_flags = TH_ACK;
            break ;
        case S_XMAS:
            template->tcpheader.th_flags |= TH_FIN;
            template->tcpheader.th_flags |= TH_PUSH;
            template->tcpheader.th_flags |= TH_URG;
            break ;
        case S_NULL:
            template->tcpheader.th_flags = 0;
            break ;
       case S_UDP:
            break ;
    }
}

static void init_tcp_packet(t_thread *thread, t_tcp_packet *template,
                            t_scan_type scan)
{
    /* Pseudo Header */
    template->saddr
        = ((struct sockaddr_in *)&(thread->src))->sin_addr.s_addr;
    template->daddr
        = ((struct sockaddr_in *)&(thread->dst))->sin_addr.s_addr;
    template->protocol              = IPPROTO_TCP;
    template->tot_len               = htons(sizeof(t_tcpheader));
    template->tcpheader.th_sport    = htons(DEFAULT_SRC_PORT + (uint16_t)scan);
}

static void update_tcp(t_tcp_packet *template, uint16_t port, t_scan_type scan)
{
    /* TCP Header */

    template->tcpheader.th_seq    = htonl(0);
    template->tcpheader.th_dport  = htons(port);
    template->tcpheader.th_off    = sizeof(t_tcpheader) / 4;
    setup_th_flags(template, scan);
    template->tcpheader.th_win    = htons(1024);
    template->tcpheader.th_sum    = in_cksum(template, sizeof(t_tcp_packet));
}

uint8_t     send_tcp(t_thread *thread, t_scan_type scan)
{
    ssize_t         bytes_sent  = 0;
    char            buffer[MAX_MTU];
    t_tcp_packet    template;
    struct iphdr    iphdr;

    ft_bzero(&iphdr, sizeof(struct iphdr));

    iphdr.version      = 4;
    iphdr.ihl          = sizeof(struct iphdr) / 4;
    iphdr.tos          = 0;
    iphdr.tot_len      = htons(sizeof(struct iphdr) + sizeof(t_tcpheader));
    iphdr.id           = 0;
    iphdr.frag_off     = htons(0);
    iphdr.ttl          = 64;
    iphdr.protocol     = IPPROTO_TCP;
    iphdr.check        = 0;
    iphdr.saddr
        = ((struct sockaddr_in *)&(thread->src))->sin_addr.s_addr;
    iphdr.daddr
        = ((struct sockaddr_in *)&(thread->dst))->sin_addr.s_addr;


    ft_bzero(&template, sizeof(template));

    init_tcp_packet(thread, &template, scan);

    for (t_list *tmp = thread->results; tmp; tmp = tmp->next)
    {
        #ifdef DEBUG
            dprintf(STDOUT_FILENO, "[DEBUG THREAD %lu] From %s\n",
                    pthread_self(),
                    inet_ntoa(((struct sockaddr_in *)&(thread->src))->sin_addr));
            dprintf(STDERR_FILENO,
                    "[DEBUG THREAD %lu] Sending packet to %s:%d |%s|\n",
                    pthread_self(),
                    inet_ntoa(((struct sockaddr_in *)&(thread->dst))->sin_addr),
                    ((t_result *)tmp->data)->port, debug_scan(scan));
        #endif

        ft_bzero(&buffer, sizeof(buffer));

        update_tcp(&template, ((t_result *)tmp->data)->port, scan);

        ft_memcpy(buffer, &iphdr, sizeof(struct iphdr));
        ft_memcpy(buffer + sizeof(struct iphdr), &template.tcpheader,
                  sizeof(template.tcpheader));

        if ((bytes_sent = sendto(thread->sockets[scan], buffer,
                                 sizeof(struct iphdr) + sizeof(template.tcpheader),
                                 0, (struct sockaddr_in *)&(thread->dst),
                                 sizeof(struct sockaddr_in))) == -1)
        {
            dprintf(STDERR_FILENO, "ft_nmap: sendto(): %s\n", strerror(errno));
            return (FAILURE);
        }
    }
    return (SUCCESS);
}
