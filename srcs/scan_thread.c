/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:57:49 by cempassi          #+#    #+#             */
/*   Updated: 2022/01/09 14:21:24 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include "memory.h"
#include "str.h"

static int      find_port(void *current, void *to_find)
{
    t_result    *result         = (t_result *)current;
    uint16_t    tmp_to_find     = *(uint16_t *)to_find;

    return (result->port == tmp_to_find ? TRUE : FALSE);
}


static void     retrieve_port_icmp(uint16_t *port, void *bytes)
{
    struct udphdr *udp = (struct udphdr *)bytes;

    *port = ntohs(udp->uh_dport);
}

static uint8_t  fetch_icmp_packet(t_thread *thread, void *bytes)
{
    struct icmphdr  *icmphdr    = (struct icmphdr *)bytes;
    t_list          *result     = NULL;
    t_result        *result_tmp = NULL;
    uint16_t        port        = 0;

    retrieve_port_icmp(&port, (char *)bytes + sizeof(struct icmphdr)
                       + sizeof(struct iphdr));

    #ifdef DEBUG
        dprintf(STDERR_FILENO, "[DEBUG THREAD %lu] Received ICMP: %hu\n",
                pthread_self(), port);
    #endif

    if (!(result = ft_lstfind(thread->results, &port,
                              (int (*)(void*, void*))find_port)))
        return (FAILURE);

    result_tmp = (t_result *)result->data;

    if (icmphdr->type == ICMP_DEST_UNREACH)
    {
        if (icmphdr->code == ICMP_PORT_UNREACH)
            result_tmp->status[S_UDP] = E_CLOSED;
        if (icmphdr->code ==
                (ICMP_NET_UNREACH | ICMP_HOST_UNREACH | ICMP_PROT_UNREACH
                    | ICMP_NET_ANO | ICMP_HOST_ANO | ICMP_PKT_FILTERED))
            result_tmp->status[S_UDP] = E_FILTERED;
    }

    return (SUCCESS);
}

static uint8_t  fetch_tcp_packet(t_thread *thread, void *bytes)
{
    struct tcphdr   *tcp        = (struct tcphdr *)bytes;
    t_list          *result     = NULL;
    t_result        *result_tmp = NULL;
    uint16_t        port        = 0;

    port = ntohs(tcp->th_sport);

    #ifdef DEBUG
        dprintf(STDERR_FILENO, "[DEBUG THREAD %lu] Received TCP: %hu\n",
                pthread_self(), port);
    #endif

    if (!(result = ft_lstfind(thread->results, &port,
                              (int (*)(void*, void*))find_port)))
        return (FAILURE);

    result_tmp = (t_result *)result->data;

    if (tcp->th_flags & TH_ACK && tcp->th_flags & TH_SYN)
        result_tmp->status[S_SYN]   = E_OPEN;
    if (tcp->th_flags & TH_RST)
    {
        result_tmp->status[S_SYN]   = E_CLOSED;
        result_tmp->status[S_NULL]  = E_CLOSED;
        result_tmp->status[S_FIN]   = E_CLOSED;
        result_tmp->status[S_XMAS]  = E_CLOSED;
        result_tmp->status[S_ACK]   = E_UNFILTERED;
    }

    return (SUCCESS);
}

static uint8_t  fetch_udp_packet(t_thread *thread, void *bytes)
{
    struct udphdr   *udp        = (struct udphdr *)bytes;
    t_list          *result     = NULL;
    t_result        *result_tmp = NULL;
    uint16_t        port        = 0;

    port = ntohs(udp->uh_sport);

    if (!(result = ft_lstfind(thread->results, &port,
                              (int (*)(void*, void*))find_port)))
        return (FAILURE);

    result_tmp = (t_result *)result->data;
    result_tmp->status[S_UDP] = E_OPEN;

    return (SUCCESS);
}




static void     packet_handler(u_char *data, const struct pcap_pkthdr *h,
                               const u_char *bytes)
{
    (void)h;
    /**/
    #pragma clang diagnostic ignored "-Wcast-align"
    #pragma clang diagnostic ignored "-Wcast-qual"
    /**/

    t_thread        *thread = (t_thread *)data;
    struct iphdr    *iphdr  = (struct iphdr *)(bytes
                              + sizeof(struct ether_header));

    if (iphdr->version == IPVERSION)
    {
        switch (iphdr->protocol)
        {
            case IPPROTO_ICMP:
                if (fetch_icmp_packet(thread, (char *)bytes
                                      + sizeof(struct ether_header)
                                      + sizeof(struct iphdr)) != SUCCESS)
                   return ;
                break;

            case IPPROTO_TCP:
                if (fetch_tcp_packet(thread, (char *)bytes
                                     + sizeof(struct ether_header)
                                     + sizeof(struct iphdr)) != SUCCESS)
                    return ;
                break;

            case IPPROTO_UDP:
                if (fetch_udp_packet(thread, (char *)bytes
                                     + sizeof(struct ether_header)
                                     + sizeof(struct iphdr)) != SUCCESS)
                    return ;
                break;

            default:
                break;
        }
    }

    #ifdef DEBUG
        dprintf(STDOUT_FILENO, "[DEBUG THREAD %lu] Received %d bytes\n",
                pthread_self(), h->caplen);
    #endif
}

static int      set_scan_window(t_thread *thread)
{
    t_list  *tmp        = thread->results;
    int     window      = 10;
    uint8_t factor      = 1;

    window = window * (int)ft_lstlen(tmp);

    if (thread->scan & SCAN_SYN)
        factor += 1;
    if (thread->scan & SCAN_ACK)
        factor += 1;
    if (thread->scan & SCAN_FIN)
        factor += 1;
    if (thread->scan & SCAN_XMAS)
        factor += 1;
    if (thread->scan & SCAN_NULL)
        factor += 1;
    if (thread->scan & SCAN_UDP)
        factor += 1;

    window = window * factor + 1000;

    #ifdef DEBUG
        dprintf(STDOUT_FILENO, "[DEBUG THREAD %lu] Scan window: %d ms\n",
                pthread_self(), window);
    #endif

    return (window);
}

static void     set_pollfds(t_thread *thread, struct pollfd *pfds)
{
    pfds[S_SYN].fd = thread->sockets[S_SYN];
    pfds[S_SYN].events = POLLIN;
    pfds[S_SYN].revents = 0;
    pfds[S_ACK].fd = thread->sockets[S_ACK];
    pfds[S_ACK].events = POLLIN;
    pfds[S_ACK].revents = 0;
    pfds[S_FIN].fd = thread->sockets[S_FIN];
    pfds[S_FIN].events = POLLIN;
    pfds[S_FIN].revents = 0;
    pfds[S_XMAS].fd = thread->sockets[S_XMAS];
    pfds[S_XMAS].events = POLLIN;
    pfds[S_XMAS].revents = 0;
    pfds[S_NULL].fd = thread->sockets[S_NULL];
    pfds[S_NULL].events = POLLIN;
    pfds[S_NULL].revents = 0;
    pfds[S_UDP].fd = thread->sockets[S_UDP];
    pfds[S_UDP].events = POLLIN;
    pfds[S_UDP].revents = 0;
    pfds[S_UDP_ICMP_RESPONSE].fd = thread->sockets[S_UDP_ICMP_RESPONSE];
    pfds[S_UDP_ICMP_RESPONSE].events = POLLIN;
    pfds[S_UDP_ICMP_RESPONSE].revents = 0;
}

static void     pcap_dispatch_handler(t_thread *thread, int window)
{
    struct pollfd   pfds[MAX_SCAN];
    struct timeval  t1, t2;
    double time     = 0.0;
    size_t fds      = MAX_SCAN;
    int window      = set_scan_window(thread);

    ft_memset(pfds, 0, sizeof(pfds));
    ft_memset(&t1, 0, sizeof(struct timeval));
    ft_memset(&t2, 0, sizeof(struct timeval));

    set_pollfds(thread, pfds);


    if (gettimeofday(&t1, NULL) < 0)
    {
        dprintf(STDERR_FILENO, "ft_nmap: gettimeofday(): %s\n",
            strerror(errno));
        pthread_exit(NULL);
    }

    while (time < window && fds)
    {
        if (poll(pfds, MAX_SCAN, window) > 0)
        {
            for (size_t i = 0; i < MAX_SCAN; i++)
            {
                if (pfds[i].revents != 0)
                {
                    if (pfds[i].revents & POLLIN)
                    {
                        #ifdef DEBUG
                            dprintf(STDERR_FILENO,
                                    "[DEBUG THREAD %lu] poll > s|%d| f|%zu|\n",
                                    pthread_self(), pfds[i].fd, i);
                        #endif

                        while (time < window)
                        {
                            if (pcap_dispatch(sniffer, 1,
                                              packet_handler,
                                              (u_char *)thread) == -1)
                            {
                                dprintf(STDERR_FILENO,
                                    "ft_nmap: pcap_dispatch(): %s\n",
                                    pcap_geterr(thread->sniffer));
                                pthread_exit(NULL);
                            }

                            if (gettimeofday(&t2, NULL) < 0)
                            {
                                dprintf(STDERR_FILENO,
                                    "ft_nmap: gettimeofday(): %s\n",
                                    strerror(errno));
                                pthread_exit(NULL);
                            }

                            time = ((double)t2.tv_sec
                                    - (double)t1.tv_sec) * 1000.0;
                            time += ((double)t2.tv_usec
                                    - (double)t1.tv_usec) / 1000.0;

                        }

                        #ifdef DEBUG
                            dprintf(STDOUT_FILENO,
                                    "[DEBUG THREAD %lu] POLLING DONE ...\n",
                                    pthread_self());
                        #endif

                        fds--;
                        break;
                    }
                    else
                        fds--;

                }
            }
        }
        else
        {
            #ifdef DEBUG
                dprintf(STDOUT_FILENO, "[DEBUG THREAD %lu] TIMEOUT !\n",
                        pthread_self());
            #endif

            break;
        }

        if (gettimeofday(&t2, NULL) < 0)
        {
            dprintf(STDERR_FILENO, "ft_nmap: gettimeofday(): %s\n",
                    strerror(errno));
            pthread_exit(NULL);
        }

        time = ((double)t2.tv_sec - (double)t1.tv_sec) * 1000.0;
        time += ((double)t2.tv_usec - (double)t1.tv_usec) / 1000.0;
    }
}

static uint8_t wait_udp_handler(void)
{
    double           start, end = 0.0;
    struct timeval   udp_ready;

    ft_memset(&udp_ready, 0, sizeof(struct timeval));

    if (gettimeofday(&udp_ready, NULL) < 0)
    {
        dprintf(STDERR_FILENO, "ft_nmap: gettimeofday(): %s\n",
                strerror(errno));
        return (FAILURE);
    }

    start = (double)udp_ready.tv_sec * 1000.0;
    start += (double)udp_ready.tv_usec / 1000.0;
    end = start;

    while (end - start < 1.0)
    {
        if (gettimeofday(&udp_ready, NULL) < 0)
        {
            dprintf(STDERR_FILENO, "ft_nmap: gettimeofday(): %s\n",
                    strerror(errno));
            return (FAILURE);
        }
        end = (double)udp_ready.tv_sec * 1000.0;
        end += (double)udp_ready.tv_usec / 1000.0;
    }

    return (SUCCESS);
}

void            *scan_thread(void *data)
{
    t_thread            *thread     = data;
    bpf_u_int32         mask        = 0;
    bpf_u_int32         net         = 0;
    struct bpf_program  compiled_filter;
    char                errbuf[PCAP_ERRBUF_SIZE];

    #ifdef DEBUG
        dprintf(STDERR_FILENO, "[DEBUG THREAD %lu] STARTING THREAD ...\n",
                pthread_self());
    #endif

    #ifdef DEBUG
        dprintf(STDOUT_FILENO, "[DEBUG THREAD %lu] FILTER |%s|\n",
                pthread_self(), thread->filter.buffer);
    #endif

    /* get network number and mask associated with capture device */
    if (pcap_lookupnet(thread->device, &net, &mask, errbuf) == -1)
    {
        dprintf(STDERR_FILENO, "ft_nmap: pcap_lookupnet(): %s: %s\n", errbuf,
                thread->device);
        pthread_exit(NULL);
    }

	/* open capture device */
    if (!(thread->sniffer = pcap_open_live(thread->device, TCP_MAXWIN, FALSE, -1,
                                   errbuf)))
    {
        dprintf(STDERR_FILENO, "ft_nmap: pcap_open_live(): %s\n", errbuf);
        pthread_exit(NULL);
    }

	/* compile the filter expression */
    if (pcap_compile(thread->sniffer, &thread->compiled_filter, thread->filter.buffer,
                     TRUE, mask) == -1)
    {
        dprintf(STDERR_FILENO, "ft_nmap: pcap_compile(): %s: %s\n",
                pcap_geterr(thread->sniffer), thread->filter.buffer);
        pthread_exit(NULL);
    }

	/* apply the compiled filter */
    if (pcap_setfilter(thread->sniffer, &thread->compiled_filter) == -1)
    {
        dprintf(STDERR_FILENO, "ft_nmap: pcap_setfilter(): %s: %s\n",
                pcap_geterr(thread->sniffer), thread->filter.buffer);
        pthread_exit(NULL);
    }

    if (pcap_setnonblock(thread->sniffer, 1, errbuf) == -1)
    {
        dprintf(STDERR_FILENO, "ft_nmap: pcap_setnonblock(): %s\n", errbuf);
        pthread_exit(NULL);
    }

    /* Send packets */
    if (scan_ports_tcp(thread) != SUCCESS)
    {
        dprintf(STDERR_FILENO, "ft_nmap: scan_ports(): Scan port error\n");
        pthread_exit(NULL);
    }

    pcap_dispatch_handler(thread, sniffer, &compiled_filter);

    if (thread->scan & SCAN_UDP)
    {
        for (t_list *tmp = thread->results; tmp; tmp = tmp->next)
        {
            t_result        *result = (t_result *)tmp->data;

            pthread_mutex_lock(&(g_nmap.lock));

            if (send_udp(thread, result->port, S_UDP) != SUCCESS)
            {
                pthread_mutex_unlock(&(g_nmap.lock));
                break ;
            }

            pcap_dispatch_handler(thread, sniffer, &compiled_filter);

            if (wait_udp_handler() == FAILURE)
            {
                pthread_mutex_unlock(&(g_nmap.lock));
                break ;
            }

            pthread_mutex_unlock(&(g_nmap.lock));
        }
    }

    #ifdef DEBUG
        dprintf(STDERR_FILENO, "[DEBUG THREAD %lu] END THREAD\n",
                pthread_self());
    #endif

    /* Clean allocated ressources and exit*/
    pthread_exit(NULL);
}
