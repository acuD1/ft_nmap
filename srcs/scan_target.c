/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_target.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:27:15 by cempassi          #+#    #+#             */
/*   Updated: 2022/01/01 12:51:27 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include "list.h"
#include "str.h"
#include "vector.h"
#include <pthread.h>
#include <stdio.h>
#include <strings.h>

// - scan_target
//     - scan_thread
//         - scan_port

static uint8_t  init_thread(t_nmap *nmap, t_target *target, t_thread *thread)
{
    thread->ports           = NULL;
    thread->src             = nmap->src;
    thread->dst             = target->dst;
    thread->scan            = nmap->scan;
	thread->filter.size     = DEFAULT_LEN_FILTER;
	thread->filter.scale    = DEFAULT_LEN_SCALE;
    if (!(thread->filter.buffer   = ft_strnew(DEFAULT_LEN_FILTER)))
        return (FAILURE);
    return (SUCCESS);
}

static uint8_t     reset_thread(t_thread *thread)
{
    thread->ports           = NULL;
	thread->filter.size     = DEFAULT_LEN_FILTER;
	thread->filter.scale    = DEFAULT_VECTOR_SCALE;
    if (!(thread->filter.buffer   = ft_strnew(DEFAULT_VECTOR_SCALE)))
        return (FAILURE);
    return (SUCCESS);
}

static uint8_t  create_thread(t_list **threads, t_thread *thread_template)
{
    if (ft_lstaddback(threads,
            ft_lstnew(thread_template, sizeof(t_thread))) != SUCCESS)
    {
        dprintf(STDERR_FILENO, "ft_nmap: create_thread(): Malloc error\n");
        return (FAILURE);
    }
    if (reset_thread(thread_template) == FAILURE)
        return (FAILURE);
    if (generate_filter_protocol(thread_template) == FAILURE)
        return (FAILURE);
    return (SUCCESS);
}

static uint8_t  add_port(t_list **ports, uint16_t port)
{
    if (ft_lstaddback(ports, ft_lstnew(&port, sizeof(uint16_t))) != SUCCESS)
    {
        dprintf(STDERR_FILENO, "ft_nmap: add_port(): Malloc error\n");
        return (FAILURE);
    }
    return (SUCCESS);
}

static void     set_range(t_port *target, uint16_t *min_port,
                            uint16_t *max_port)
{

    if (target->data.range[1] > target->data.range[0])
    {
        *min_port = target->data.range[0];
        *max_port = target->data.range[1];
    }
    else
    {
        *min_port = target->data.range[1];
        *max_port = target->data.range[0];
    }
}

static uint8_t  add_single_port_handler(t_thread *thread, uint16_t port)
{
    if (generator_filter_or(thread) == FAILURE)
        return (FAILURE);
    if (generate_filter_port_single(thread, port) == FAILURE)
        return (FAILURE);
    if (add_port(&thread->ports, port) == FAILURE)
        return (FAILURE);
    return (SUCCESS);
}

static uint8_t  dispatch_leftovers(t_list *ports, t_list *threads,
                                  uint16_t min_port)
{
    t_list   *current_port  = ports;
    t_list   *tmp           = threads;
    uint16_t max_port       = 0;
    uint16_t holder         = 0;

    while(tmp && ports)
    {
        t_port *target_port = ports->data;
        if (target_port->type == E_PORT_SINGLE)
        {
            t_thread *thread = tmp->data;
            if (add_single_port_handler(thread,
                    target_port->data.port) == FAILURE)
                return (FAILURE);
        }
        else
        {
            holder = min_port;
            set_range(target_port, &min_port, &max_port);
            if (current_port == ports)
                min_port = holder;
            while (min_port <= max_port && tmp)
            {
                t_thread *thread = tmp->data;
                if (add_single_port_handler(thread, min_port) == FAILURE)
                    return (FAILURE);
                tmp = tmp->next;
                min_port++;
            }
            ports = ports->next;
            continue;
        }
        tmp = tmp->next;
        ports = ports->next;
    }
    return (SUCCESS);
}

static t_list *generate_threads(t_target *target, t_thread *thread_template)
{
    t_list      *threads            = NULL;
    uint16_t    port_nbr            = 0;
    uint16_t    dispatched_ports    = 0;
    uint16_t    min_port            = 0;
    uint16_t    max_port            = 0;
    uint16_t    start_port          = 0;

    for (t_list *current = target->ports; current; current = current->next)
    {
        if (dispatched_ports >= target->port_nbr - target->port_leftover)
        {
            if (dispatch_leftovers(current, threads, 0) == FAILURE)
                return (NULL);
        }
        else
        {
            t_port *target_port = current->data;
            if (target_port->type == E_PORT_SINGLE)
            {
                port_nbr++;
                dispatched_ports++;
                if (add_port(&thread_template->ports,
                        target_port->data.port) == FAILURE)
                    return (NULL);
                if (generate_filter_port_single(thread_template,
                        target_port->data.port) == FAILURE)
                    return (NULL);
                if (port_nbr == target->port_per_thread)
                {
                    if (create_thread(&threads, thread_template) == SUCCESS)
                        port_nbr = 0;
                    else
                    {
                        //FIXME: Free previous on failure
                        return (NULL);
                    }
                }
            }
            else
            {
                set_range(target_port, &min_port, &max_port);
                start_port = min_port;
                while (min_port <= max_port)
                {
                    port_nbr++;
                    dispatched_ports++;
                    if (add_port(&thread_template->ports, min_port) == FAILURE)
                        return (NULL);
                    if (port_nbr == target->port_per_thread)
                    {
                        if (start_port != min_port)
                        {
                            if (generate_filter_port_range(thread_template,
                                    start_port, min_port) == FAILURE)
                                return (NULL);
                        }
                        else
                        {
                            if (generate_filter_port_single(thread_template,
                                    min_port) == FAILURE)
                                return (NULL);
                        }
                        start_port = min_port + 1;
                        if (create_thread(&threads, thread_template) == SUCCESS)
                            port_nbr = 0;
                        else
                        {
                            //FIXME: Free previous on failure
                            return (NULL);
                        }
                    }
                    min_port++;
                    if (dispatched_ports >= target->port_nbr - target->port_leftover)
                    {
                        if (dispatch_leftovers(current, threads, min_port) == FAILURE)
                            return (NULL);
                        return(threads);
                    }
                }
            }
            if (port_nbr != 0)
                generator_filter_or(thread_template);
        }
    }
    return (threads);
}

int     scan_target(void *data, void *context)
{
    t_nmap      *nmap       = context;
    t_target    *target     = data;
    t_list      *threads    = NULL;
    t_list      *threads_id = NULL;
    t_thread     thread_data_template;

    print_target(target);

    // Reset global
    g_nmap.seq      = 0;
    g_nmap.src_port = DEFAULT_SRC_PORT;

    // Set base values
    init_thread(nmap, target, &thread_data_template);

    if (generate_filter_protocol(&thread_data_template) == FAILURE)
        return (FAILURE);

    // 1: Ports repartition between treads
    if ((threads = generate_threads(target, &thread_data_template)) == NULL)
        return (FAILURE);

    if (generate_filter_src(threads) == FAILURE)
         return (FAILURE);

    // 2: Launch threads and collect their identifiers in a list of pthread_t
    for (t_list *tmp = threads; tmp; tmp = tmp->next)
    {
        // Thread identifier
        pthread_t   tid = 0;
        int         result;

        result = pthread_create(&tid, NULL, scan_thread, tmp->data);
        if (result != SUCCESS
            || ft_lstaddback(&threads_id, ft_lstnew(&tid, sizeof(pthread_t)))
                != SUCCESS)
        {
            ft_strdel(&thread_data_template.filter.buffer);
            ft_lstdel(&threads, delete_thread);
            ft_lstdel(&threads_id, NULL);
            return (FAILURE);
        }
    }


    // 3: Join on each launched thread
    for (t_list *tmp = threads_id; tmp; tmp = tmp->next)
    {
        pthread_t   *tid = tmp->data;
        int         result;

        result = pthread_join(*tid, NULL);
        if (result != SUCCESS)
        {
            ft_strdel(&thread_data_template.filter.buffer);
            ft_lstdel(&threads, delete_thread);
            ft_lstdel(&threads_id, NULL);
        }
    }

    // 4: Cleanup and exit
    ft_strdel(&thread_data_template.filter.buffer);
    ft_lstdel(&threads, delete_thread);
    ft_lstdel(&threads_id, NULL);
    return (SUCCESS);
}
