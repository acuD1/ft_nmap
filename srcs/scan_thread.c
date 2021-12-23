/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:57:49 by cempassi          #+#    #+#             */
/*   Updated: 2021/12/19 20:54:02 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include "memory.h"
#include "str.h"

static char *generate_filter(t_thread *thread)
{
    (void)thread;
    return ft_strdup("(tcp port 53 or 443) and (src 8.8.8.8 or 1.1.1.1)");
}

static uint8_t setup_sockfd(struct sockaddr_in *dst, int *sockfd)
{
    if ((*sockfd = socket(dst->sin_family, SOCK_RAW, IPPROTO_TCP)) == -1)
    {
        printf("[DEBUG] socket(): ERROR: %s , errno %d\n", strerror(errno), errno);
        return (FAILURE);
    }
    return (SUCCESS);
}

static void init_packet(t_thread *thread, t_tcp_packet *template)
{
    t_ipheader *iphdr = &template->ipheader;


    /* Pseudo Header */
	template->ipheader.saddr            = (struct sockaddr_in *)&(thread->src);
	template->ipheader.daddr            = (struct sockaddr_in *)&(thread->dst);
	template->ipheader.protocol         = IPPROTO_TCP;
	template->ipheader.tcp_len          = (struct sockaddr_in *)&(thread->dst);


}

static void update_tcp(t_tcp_packet *template, uint16_t port, t_scan_type scan)
{
    t_ipheader *iphdr = &template->ipheader;

	/* TCP Header */
	template->tcpheader.th_sport  = src->sin_port;
	template->tcpheader.th_dport  = dest->sin_port;
	template->tcpheader.th_seq    = htonl(static_seq++);
	template->tcpheader.th_off    = sizeof(struct tcphdr) / 4;
}

static uint8_t send_tcp(t_thread *thread, t_scan_type scan)
{
    t_tcp_packet    template;
    uint16_t        tmp_s_port      = 33000;

    ft_bzero(&template, sizeof(template));
    init_packet(thread, &template);
    if (setup_sockfd((struct sockaddr_in *)&(thread->dst), thread->sockets + scan) != SUCCESS)
        return (FAILURE);
    for(t_list *tmp = thread->ports; tmp; tmp = tmp->next)
    {
        update_tcp(&template, scan);
        send_packet(&template);
    }
    return (SUCCESS);
}

uint8_t scan_ports(t_thread *thread)
{
    if (thread->scan & SCAN_SYN)
    {
        send_tcp(thread, S_ACK);
    }
    if (thread->scan & SCAN_NULL)
    {
        send_tcp(thread, S_NULL);
    }
    if (thread->scan & SCAN_ACK)
    {
        send_tcp(thread, S_ACK);
    }
    if (thread->scan & SCAN_FIN)
    {
        send_tcp(thread, S_FIN );
    }
    if (thread->scan & SCAN_XMAS)
    {
        send_tcp(thread, S_XMAS );
    }
    else
    {
    }

    return (SUCCESS);
}

void *scan_thread(void *data)
{
    t_thread            *thread     = data;
    pcap_t              *sniffer    = NULL;
    char                *filter_str = NULL;
    bpf_u_int32         mask        = 0;
    bpf_u_int32         net         = 0;
    struct bpf_program  compiled_filter;
    char                errbuf[PCAP_ERRBUF_SIZE];
    //int                status = 0;

    /* find a capture device if not specified on command-line */
    dprintf(STDERR_FILENO, "[DEBUG THREAD %lu] STARTING THREAD ...\n", pthread_self());

	/* get network number and mask associated with capture device */
    if (pcap_lookupnet(g_nmap->device, &net, &mask, errbuf) == -1)
    {
        dprintf(STDERR_FILENO, "ft_nmap: pcap_lookupnet(): %s: %s\n", errbuf, g_nmap->device);
        pthread_exit(NULL);
    }

	/* open capture device */
    if (!(sniffer = pcap_open_live(g_nmap->device, TCP_MAXWIN, FALSE, 1000, errbuf)))
    {
        dprintf(STDERR_FILENO, "ft_nmap: pcap_open_live(): %s\n", errbuf);
        pthread_exit(NULL);
    }

    /* Generate filter string at this point */
    if((filter_str = generate_filter(thread)) == NULL)
        pthread_exit(NULL);

	/* compile the filter expression */
    if (pcap_compile(sniffer, &compiled_filter, filter_str, TRUE, mask) == -1)
    {
        dprintf(STDERR_FILENO, "ft_nmap: pcap_compile(): %s: %s\n", pcap_geterr(sniffer), filter_str);
        pthread_exit(NULL);
    }

	/* apply the compiled filter */
    if (pcap_setfilter(sniffer, &compiled_filter) == -1)
    {
        dprintf(STDERR_FILENO, "ft_nmap: pcap_setfilter(): %s: %s\n", pcap_geterr(sniffer), filter_str);
        ft_strdel(&filter_str);
        pthread_exit(NULL);
    }

    /* Send packets */
    scan_ports(thread);

    /* Recieve packets */

    /* Clean allocated ressources */
    if (compiled_filter.bf_insns)
        free(compiled_filter.bf_insns);
    pcap_close(sniffer);
    ft_strdel(&filter_str);
    dprintf(STDERR_FILENO, "[DEBUG THREAD %lu] END THREAD\n", pthread_self());
    pthread_exit(NULL);
}
