/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 12:30:31 by arsciand          #+#    #+#             */
/*   Updated: 2021/08/15 14:10:14 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void threads_generator(t_nmap *nmap, pthread_t *pthreads)
{
    t_thread_data   *tmp    = NULL;
    int             status  = 0;

    for (t_list *threads = nmap->threads; threads; threads = threads->next)
    {
        tmp = (t_thread_data *)threads->data;
        if ((status = pthread_create(pthreads + tmp->thread_id, NULL, &DEV_exec_thread, (void *)tmp)) != SUCCESS)
        {
            dprintf(STDERR_FILENO, "ft_nmap: pthread_create(): %s", strerror(status));
            ft_memdel((void *)&pthreads);
            exit_routine(nmap, FAILURE);
        }
    }
}


void        exec_nmap(t_nmap *nmap)
{
    pthread_t   *pthreads = NULL;

    if (getuid() != 0)
    {
        dprintf(STDERR_FILENO, "ft_nmap: socket: Operation not permitted\n");
        exit_routine(nmap, FAILURE);
    }

    if (!(pthreads = ft_memalloc(sizeof(pthread_t) * ft_lstlen(nmap->threads))))
    {
        dprintf(STDERR_FILENO, "[FATAL] malloc error !\n");
        exit_routine(nmap, FAILURE);
    }

    /* Disabled for now */
    // if (nmap->options)
    //     ft_lstiter_ctx(nmap->target, nmap, send_target);

    /*
    ** THREADS DATA generator function here !
    */

    threads_generator(nmap, pthreads);
    ft_memdel((void *)&pthreads);
}
