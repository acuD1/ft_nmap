/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 12:30:31 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/12 11:00:04 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void    print_scans(uint8_t scan)
{
    if (scan & SCAN_SYN)
        dprintf(STDOUT_FILENO, " SYN");
    if (scan & SCAN_ACK)
        dprintf(STDOUT_FILENO, " ACK");
    if (scan & SCAN_FIN)
        dprintf(STDOUT_FILENO, " FIN");
    if (scan & SCAN_XMAS)
        dprintf(STDOUT_FILENO, " XMAS");
    if (scan & SCAN_NULL)
        dprintf(STDOUT_FILENO, " NULL");
    if (scan & SCAN_UDP)
        dprintf(STDOUT_FILENO, " UDP");
}

void    exec_nmap(t_nmap *nmap)
{
    if (getuid() != 0)
    {
        dprintf(STDERR_FILENO, "ft_nmap: socket: Operation not permitted\n");
        exit_routine(nmap, FAILURE);
    }

    for (t_list *target = nmap->targets; target; target = target->next)
    {
        double          start, end  = 0.0;
        struct timeval  time;

        if (gettimeofday(&time, NULL) == -1)
        {
            dprintf(STDERR_FILENO, "ft_nmap: gettimeofday(): %s\n",
                    strerror(errno));
            exit_routine(nmap, EXIT_FAILURE);
        }

        start = (double)time.tv_sec
                + (double)time.tv_usec / 1000000;

        if (g_nmap.is_canceld == TRUE)
            exit_routine(nmap, FAILURE);

        #ifdef DEBUG
            debug_source_ip(target->data);
        #endif

        t_target *target_data = (t_target *)target->data;

        dprintf(STDOUT_FILENO, "Source IP: %s\n", inet_ntoa(((struct sockaddr_in *)&target_data->src)->sin_addr));
        dprintf(STDOUT_FILENO, "Target IP: %s\n", inet_ntoa(((struct sockaddr_in *)&target_data->dst)->sin_addr));
        dprintf(STDOUT_FILENO, "Number of ports: %d\n", target_data->port_nbr);
        dprintf(STDOUT_FILENO, "Device: %s\n", target_data->device);
        dprintf(STDOUT_FILENO, "Speedup: %d\n", nmap->threads);
        dprintf(STDOUT_FILENO, "Scan:");
        print_scans(nmap->scan);
        dprintf(STDOUT_FILENO, "\nScanning ...\n");

        if (scan_target(target_data, nmap) == FAILURE)
        {
            dprintf(STDERR_FILENO,
                "ft_nmap: scan_target(): An error has occured\n");
            exit_routine(nmap, EXIT_FAILURE);
        }

        if (gettimeofday(&time, NULL) == -1)
        {
            dprintf(STDERR_FILENO, "ft_nmap: gettimeofday(): %s\n",
                    strerror(errno));
            exit_routine(nmap, EXIT_FAILURE);
        }

        end = (double)time.tv_sec
                + (double)time.tv_usec / 1000000;

        dprintf(STDOUT_FILENO, "%s\n", BORDER);
        dprintf(STDOUT_FILENO, "Scan finished in %.6f seconds\n", end - start);

        if (target->next)
            dprintf(STDOUT_FILENO, "%s\n", BORDER);
    }
}
