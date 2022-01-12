/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_target.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:27:15 by cempassi          #+#    #+#             */
/*   Updated: 2022/01/12 10:41:28 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

// - scan_target
//     - scan_thread
//         - scan_port

static int      sort_target(void *context, void *data)
{
    t_result *left = (t_result *)context;
    t_result *right = (t_result *)data;
    if (left->port < right->port)
        return (-1);
    else if (left->port > right->port)
        return (1);
    else
        return (0);
}

static uint8_t  close_fds(t_thread *thread)
{
    if (thread->scan & SCAN_SYN)
    {
        if (close(thread->sockets[S_SYN]) == -1)
            return (FAILURE);
    }
    if (thread->scan & SCAN_ACK)
    {
        if (close(thread->sockets[S_ACK]) == -1)
            return (FAILURE);
    }
    if (thread->scan & SCAN_FIN)
    {
        if (close(thread->sockets[S_FIN]) == -1)
            return (FAILURE);
    }
    if (thread->scan & SCAN_XMAS)
    {
        if (close(thread->sockets[S_XMAS]) == -1)
            return (FAILURE);
    }
    if (thread->scan & SCAN_NULL)
    {
        if (close(thread->sockets[S_NULL]) == -1)
            return (FAILURE);
    }
    if (thread->scan & SCAN_UDP)
    {
        if (close(thread->sockets[S_UDP]) == -1)
            return (FAILURE);
        if (close(thread->sockets[S_UDP_ICMP_RESPONSE]) == -1)
            return (FAILURE);
    }
    return (SUCCESS);
}

/* In case of sigint when creating threads, we need to join all threads
before cleanup */
static uint8_t  cleaner_joined_thread(t_list *threads, t_list *threads_id)
{
    for (t_list *tmp = threads_id; tmp; tmp = tmp->next)
    {
        pthread_t   *tid = tmp->data;

        if (pthread_join(*tid, NULL) != SUCCESS)
            dprintf(STDERR_FILENO,
                "ft_nmap: pthread_join(): Error joining thread %lu\n", *tid);
    }

    ft_lstdel(&threads, delete_thread);
    ft_lstdel(&threads_id, NULL);
    return (FAILURE);
}

int             scan_target(void *data, void *context)
{
    t_nmap      *nmap       = context;
    t_target    *target     = data;
    t_list      *threads    = NULL;
    t_list      *threads_id = NULL;
    t_list      *results    = NULL;
    long long   result      = 0;

    #ifdef DEBUG
        debug_target(target);
    #endif

    // 1: Ports repartition between treads
    if (generate_threads(&threads, target, nmap->scan) != SUCCESS)
    {
        ft_lstdel(&threads, delete_thread);
        return (FAILURE);
    }

    if (g_nmap.is_canceld == TRUE)
    {
        ft_lstdel(&threads, delete_thread);
        return (FAILURE);
    }

    // 2: Launch threads and collect their identifiers in a list of pthread_t
    for (t_list *tmp = threads; tmp; tmp = tmp->next)
    {
        pthread_t   tid = 0;

        if (g_nmap.is_canceld == TRUE)
            return (cleaner_joined_thread(threads, threads_id));

        if (pthread_create(&tid, NULL, scan_thread, tmp->data) != SUCCESS
            || ft_lstaddback(&threads_id, ft_lstnew(&tid, sizeof(pthread_t)))
                != SUCCESS)
        {
            dprintf(STDERR_FILENO, "ft_nmap: scan_target(): Error creating thread\n");
            return (cleaner_joined_thread(threads, threads_id));
        }
    }

    // 3: Join on each launched thread
    for (t_list *tmp = threads_id; tmp; tmp = tmp->next)
    {
        pthread_t   *tid = tmp->data;

        pthread_join(*tid, (void *)&result);

    }

    if ((void *)result == PTHREAD_CANCELED)
    {
        ft_lstdel(&threads, delete_thread);
        ft_lstdel(&threads_id, NULL);
        return (FAILURE);
    }


    if (g_nmap.is_canceld == TRUE)
    {
        ft_lstdel(&threads, delete_thread);
        ft_lstdel(&threads_id, NULL);
        return (FAILURE);
    }

    if (close_fds(threads->data) != SUCCESS)
    {
        dprintf(STDERR_FILENO, "ft_nmap: close_fds(): failed\n");
        ft_lstdel(&threads, delete_thread);
        ft_lstdel(&threads_id, NULL);
        return (FAILURE);
    }
    else
    {
        for (t_list *tmp = threads; tmp; tmp = tmp->next)
        {
            t_thread *thread = tmp->data;

            if (g_nmap.is_canceld == TRUE)
            {
                ft_lstdel(&threads, delete_thread);
                ft_lstdel(&threads_id, NULL);
                ft_lstdel(&results, NULL);
                return (FAILURE);
            }

            /* Add results to the local target results list */
            ft_lstmerge(&results, thread->results);
            thread->results = NULL;
        }

        /* Sort results by port*/
        ft_mergesort(&results, sort_target);

        /* Display results */
        dprintf(STDOUT_FILENO, "%s\n", BORDER);
        dprintf(STDOUT_FILENO, "%-*s| %-8s| %-16s| %-10s\n", 16,
                "ADDRESS", "PORT", "SERVICE", "RESULT");
        dprintf(STDOUT_FILENO, "%s\n", BORDER);
        ft_lstiter(results, display_results);
    }

    // 4: Cleanup and exit
    ft_lstdel(&threads, delete_thread);
    ft_lstdel(&threads_id, NULL);
    ft_lstdel(&results, NULL);
    return (SUCCESS);
}
