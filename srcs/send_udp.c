/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_udp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:42:16 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/09 09:32:24 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void init_udp_packet(t_thread *thread, t_udp_packet *template,
                            t_scan_type scan)
{
    /* Pseudo Header */
    template->saddr
        = ((struct sockaddr_in *)&(thread->src))->sin_addr.s_addr;
    template->daddr
        = ((struct sockaddr_in *)&(thread->dst))->sin_addr.s_addr;
    template->protocol          = IPPROTO_UDP;
    template->tot_len           = htons(sizeof(t_udpheader));

    pthread_mutex_lock(&(g_nmap.lock));
    template->udpheader.source  = htons(g_nmap.src_port + (uint16_t)scan);
    pthread_mutex_unlock(&(g_nmap.lock));
}

static void update_udp(t_udp_packet *template, uint16_t port,
                       t_udp_payload *udp_payload)
{
    /* UDP Header */
    (void)udp_payload;

    template->udpheader.dest         = htons(port);
    template->udpheader.len          = htons(8);
    template->udpheader.check        = in_cksum(template, sizeof(t_udp_packet));
}

uint8_t     send_udp(t_thread *thread, t_scan_type scan)
{
    t_udp_packet    template;
    t_udp_payload   payload;
    ssize_t         bytes_sent          = 0;
    char            buffer[MAX_MTU];

    struct iphdr       iphdr;

    ft_bzero(&iphdr, sizeof(struct iphdr));

    iphdr.version      = 4;
    iphdr.ihl          = sizeof(struct iphdr) / 4;
    iphdr.tos          = 0;
    iphdr.id           = 0;
    iphdr.frag_off     = htons(0);
    iphdr.ttl          = 64;
    iphdr.protocol     = IPPROTO_UDP;
    iphdr.check        = 0;
    iphdr.saddr
        = ((struct sockaddr_in *)&(thread->src))->sin_addr.s_addr;
    iphdr.daddr
        = ((struct sockaddr_in *)&(thread->dst))->sin_addr.s_addr;

    ft_bzero(&template, sizeof(template));
    init_udp_packet(thread, &template, scan);

    for(t_list *tmp = thread->results; tmp; tmp = tmp->next)
    {
        ft_bzero(&buffer, sizeof(buffer));
        ft_bzero(&payload, sizeof(payload));

        #ifdef DEBUG
            dprintf(STDERR_FILENO,
                    "[DEBUG THREAD %lu] Sending packet to %s:%d |%s|\n",
                    pthread_self(),
                    inet_ntoa(((struct sockaddr_in *)&(thread->dst))->sin_addr),
                    ((t_result *)tmp->data)->port, debug_scan(scan));
        #endif

        // Fix loopback not handling correctly customs payload
        if (is_loopback((struct sockaddr_in *)&(thread->dst)) != SUCCESS)
            udp_payload(&payload, ((t_result *)tmp->data)->port);

        update_udp(&template, ((t_result *)tmp->data)->port, &payload);

        iphdr.tot_len           = htons(sizeof(struct iphdr)
                                        + sizeof(template.udpheader)
                                        + payload.payload_len);

        template.udpheader.len  = htons(8 + payload.payload_len);

        ft_memcpy(buffer, &iphdr, sizeof(struct iphdr));
        ft_memcpy(buffer + sizeof(struct iphdr),
                  &template.udpheader,
                  sizeof(template.udpheader));

        if (payload.payload_len > 0)
             ft_memcpy(buffer + sizeof(struct iphdr)
                       + sizeof(template.udpheader), payload.payload,
                       payload.payload_len);

        if ((bytes_sent = sendto(thread->sockets[S_UDP], buffer,
                                 sizeof(struct iphdr)
                                 + sizeof(template.udpheader)
                                 + payload.payload_len, 0,
                                (struct sockaddr_in *)&(thread->dst),
                                sizeof(struct sockaddr_in))) == -1)
        {
            dprintf(STDERR_FILENO, "ft_nmap: sendto(): %s\n", strerror(errno));
            return (FAILURE);
        }
    }
    return (SUCCESS);
}
