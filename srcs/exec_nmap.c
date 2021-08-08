/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 12:30:31 by arsciand          #+#    #+#             */
/*   Updated: 2021/08/08 12:55:34 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void *TEST_THREAD(void *data)
{
    size_t  thread_id = (size_t)data;

    dprintf(STDERR_FILENO, "[DEBUG] Thread -%zu- working ...\n", thread_id);
    pthread_exit(NULL);
}

static void threads_generator(t_nmap *nmap, pthread_t *nmap_threads)
{
    int status = 0;

    for (size_t thread_id = 0; thread_id < nmap->threads; thread_id++)
    {
        if ((status = pthread_create(nmap_threads + thread_id, NULL, &TEST_THREAD, (void *)thread_id)) != SUCCESS)
        {
            dprintf(STDERR_FILENO, "ft_nmap: pthread_create(): %s", strerror(status));
            ft_memdel((void *)&nmap_threads);
            exit_routine(nmap, FAILURE);
        }
    }
}

static void threads_gatherer(t_nmap *nmap, pthread_t *nmap_threads)
{
    int status = 0;

    for (size_t thread_id = 0; thread_id < nmap->threads; thread_id++)
    {
        if ((status = pthread_join(nmap_threads[thread_id], NULL)) != SUCCESS)
        {
            dprintf(STDERR_FILENO, "ft_nmap: pthread_join(): %s", strerror(status));
            ft_memdel((void *)&nmap_threads);
            exit_routine(nmap, FAILURE);
        }
        dprintf(STDERR_FILENO, "[DEBUG] Thread -%zu- terminated !\n", thread_id);
    }
}

void        exec_nmap(t_nmap *nmap)
{
    pthread_t   *nmap_threads = NULL;

    if (getuid() != 0)
    {
        dprintf(STDERR_FILENO, "ft_nmap: socket: Operation not permitted\n");
        exit_routine(nmap, FAILURE);
    }

    if (!(nmap_threads = ft_memalloc(sizeof(pthread_t) * nmap->threads)))
    {
        dprintf(STDERR_FILENO, "[FATAL] malloc error !\n");
        exit_routine(nmap, FAILURE);
    }

    /* Disabled for now */
    // if (nmap->options)
    //     ft_lstiter_ctx(nmap->target, nmap, send_target);

    threads_generator(nmap, nmap_threads);
    threads_gatherer(nmap, nmap_threads);
    ft_memdel((void *)&nmap_threads);
}
