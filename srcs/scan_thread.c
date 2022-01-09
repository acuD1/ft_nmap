/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:57:49 by cempassi          #+#    #+#             */
/*   Updated: 2022/01/02 14:32:11 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include "memory.h"
#include "str.h"

static uint8_t setup_sockfd(struct sockaddr_in *dst, int *sockfd, uint8_t protocol)
{
    if ((*sockfd = socket(dst->sin_family, SOCK_RAW, protocol)) == -1)
    {
        dprintf(STDERR_FILENO, "ft_nmap: socket(): %s", strerror(errno));
        return (FAILURE);
    }
    return (SUCCESS);
}

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

//   -sS/sT/sA/sW/sM: TCP SYN/Connect()/ACK/Window/Maimon scans
//   -sU: UDP Scan
//   -sN/sF/sX: TCP Null, FIN, and Xmas scans
//   --scanflags <flags>: Customize TCP scan flags
//   -sI <zombie host[:probeport]>: Idle scan
//   -sY/sZ: SCTP INIT/COOKIE-ECHO scans
//   -sO: IP protocol scan
//   -b <FTP relay host>: FTP bounce scan

static void init_tcp_packet(t_thread *thread, t_tcp_packet *template, t_scan_type scan)
{
    /* Pseudo Header */
    template->saddr            = ((struct sockaddr_in *)&(thread->src))->sin_addr.s_addr;
    template->daddr            = ((struct sockaddr_in *)&(thread->dst))->sin_addr.s_addr;
    template->protocol         = IPPROTO_TCP;
    template->tot_len          = htons(sizeof(t_tcpheader));
    pthread_mutex_lock(&(g_nmap.lock));
    template->tcpheader.th_sport  = htons(g_nmap.src_port + (uint16_t)scan);
    pthread_mutex_unlock(&(g_nmap.lock));
}

static void init_udp_packet(t_thread *thread, t_udp_packet *template, t_scan_type scan)
{
    /* Pseudo Header */
    template->saddr            = ((struct sockaddr_in *)&(thread->src))->sin_addr.s_addr;
    template->daddr            = ((struct sockaddr_in *)&(thread->dst))->sin_addr.s_addr;
    template->protocol         = IPPROTO_UDP;
    template->tot_len          = htons(sizeof(t_udpheader));
    pthread_mutex_lock(&(g_nmap.lock));
    template->udpheader.source       = htons(g_nmap.src_port + (uint16_t)scan);
    pthread_mutex_unlock(&(g_nmap.lock));
}

static void update_tcp(t_tcp_packet *template, uint16_t port, t_scan_type scan)
{
    /* TCP Header */
    pthread_mutex_lock(&(g_nmap.lock));
    template->tcpheader.th_seq    = htonl(g_nmap.seq++);
    pthread_mutex_unlock(&(g_nmap.lock));
    template->tcpheader.th_dport  = htons(port);
    template->tcpheader.th_off    = sizeof(t_tcpheader) / 4;
    setup_th_flags(template, scan);
    template->tcpheader.th_win    = htons(1024);
    template->tcpheader.th_sum    = in_cksum(template, sizeof(t_tcp_packet));
}

static void update_udp(t_udp_packet *template, uint16_t port)
{
    /* UDP Header */

    template->udpheader.dest         = htons(port);
    template->udpheader.len          = htons(8);
    template->udpheader.check        = in_cksum(template, sizeof(t_udp_packet));
}

static uint8_t send_tcp(t_thread *thread, t_scan_type scan)
{
    t_tcp_packet    template;
    ssize_t         bytes_sent  = 0;

    ft_bzero(&template, sizeof(template));
    init_tcp_packet(thread, &template, scan);
    if (setup_sockfd((struct sockaddr_in *)&(thread->dst), thread->sockets + scan, IPPROTO_TCP) != SUCCESS)
        return (FAILURE);
    for(t_list *tmp = thread->ports; tmp; tmp = tmp->next)
    {
        dprintf(STDERR_FILENO, "[DEBUG THREAD %lu] Sending packet to %s:%d\t|%s|\n",
                pthread_self(), inet_ntoa(((struct sockaddr_in *)&(thread->dst))->sin_addr),
                *(uint16_t *)tmp->data, debug_scan(scan));

        update_tcp(&template, *(uint16_t *)tmp->data, scan);
        if ((bytes_sent = sendto(thread->sockets[scan], &template.tcpheader, sizeof(t_tcpheader), 0,
                                (struct sockaddr_in *)&(thread->dst), sizeof(struct sockaddr_in))) == -1)
        {
            dprintf(STDERR_FILENO, "ft_nmap: sendto(): %s\n", strerror(errno));
            return (FAILURE);
        }
    }
    return (SUCCESS);
}

static uint8_t send_udp(t_thread *thread, t_scan_type scan)
{
    t_udp_packet    template;
    ssize_t         bytes_sent  = 0;

    ft_bzero(&template, sizeof(template));
    init_udp_packet(thread, &template, scan);
    if (setup_sockfd((struct sockaddr_in *)&(thread->dst), thread->sockets + scan, IPPROTO_UDP) != SUCCESS)
        return (FAILURE);
    for(t_list *tmp = thread->ports; tmp; tmp = tmp->next)
    {
        dprintf(STDERR_FILENO, "[DEBUG THREAD %lu] Sending packet to %s:%d\t|%s|\n",
                pthread_self(), inet_ntoa(((struct sockaddr_in *)&(thread->dst))->sin_addr),
                *(uint16_t *)tmp->data, debug_scan(scan));

        update_udp(&template, *(uint16_t *)tmp->data);
        if ((bytes_sent = sendto(thread->sockets[scan], &template.udpheader, sizeof(t_udpheader), 0,
                                (struct sockaddr_in *)&(thread->dst), sizeof(struct sockaddr_in))) == -1)
        {
            dprintf(STDERR_FILENO, "ft_nmap: sendto(): %s\n", strerror(errno));
            return (FAILURE);
        }
    }
    return (SUCCESS);
}

uint8_t scan_ports(t_thread *thread)
{
    if (thread->scan & DEFAULT_SCAN)
    {
        for (int i = 0; i < 5; i++)
            if (send_tcp(thread, (t_scan_type)i) == FAILURE)
                return (FAILURE);
        if ((send_udp(thread, S_UDP) != SUCCESS))
            return (FAILURE);
        return (SUCCESS);
    }
    if (thread->scan & SCAN_SYN)
        send_tcp(thread, S_SYN);
    if (thread->scan & SCAN_NULL)
        send_tcp(thread, S_NULL);
    if (thread->scan & SCAN_ACK)
        send_tcp(thread, S_ACK);
    if (thread->scan & SCAN_FIN)
        send_tcp(thread, S_FIN );
    if (thread->scan & SCAN_XMAS)
        send_tcp(thread, S_XMAS);
    if (thread->scan & SCAN_UDP)
        send_udp(thread, S_UDP);
    return (SUCCESS);
}

void *scan_thread(void *data)
{
    t_thread            *thread     = data;
    pcap_t              *sniffer    = NULL;
    bpf_u_int32         mask        = 0;
    bpf_u_int32         net         = 0;
    struct bpf_program  compiled_filter;
    char                errbuf[PCAP_ERRBUF_SIZE];

    /* find a capture device if not specified on command-line */
    dprintf(STDERR_FILENO, "[DEBUG THREAD %lu] STARTING THREAD ...\n", pthread_self());

    dprintf(STDOUT_FILENO, "[DEBUG THREAD %lu] FILTER |%s|\n", pthread_self(), thread->filter.buffer);

    /* get network number and mask associated with capture device */
    if (pcap_lookupnet(thread->device, &net, &mask, errbuf) == -1)
    {
        dprintf(STDERR_FILENO, "ft_nmap: pcap_lookupnet(): %s: %s\n", errbuf,
                thread->device);
        close_thread(sniffer, &compiled_filter);
    }

	/* open capture device */
    if (!(sniffer = pcap_open_live(thread->device, TCP_MAXWIN, FALSE, -1,
                                   errbuf)))
    {
        dprintf(STDERR_FILENO, "ft_nmap: pcap_open_live(): %s\n", errbuf);
        pthread_exit(NULL);
    }

	/* compile the filter expression */
    if (pcap_compile(sniffer, &compiled_filter, thread->filter.buffer, TRUE, mask) == -1)
    {
        dprintf(STDERR_FILENO, "ft_nmap: pcap_compile(): %s: %s\n", pcap_geterr(sniffer), thread->filter.buffer);
        pthread_exit(NULL);
    }

	/* apply the compiled filter */
    if (pcap_setfilter(sniffer, &compiled_filter) == -1)
    {
        dprintf(STDERR_FILENO, "ft_nmap: pcap_setfilter(): %s: %s\n", pcap_geterr(sniffer), thread->filter.buffer);
        pthread_exit(NULL);
    }

    /* Send packets */
    if (scan_ports(thread) != SUCCESS)
    {
        if (compiled_filter.bf_insns)
            free(compiled_filter.bf_insns);
        pcap_close(sniffer);
        dprintf(STDERR_FILENO, "[DEBUG THREAD %lu] SCAN PORT ERROR !\n", pthread_self());
        pthread_exit(NULL);
    }

    /* Recieve packets */

    /* Clean allocated ressources */
    if (compiled_filter.bf_insns)
        free(compiled_filter.bf_insns);
    pcap_close(sniffer);
    dprintf(STDERR_FILENO, "[DEBUG THREAD %lu] END THREAD\n", pthread_self());
    pthread_exit(NULL);
}
