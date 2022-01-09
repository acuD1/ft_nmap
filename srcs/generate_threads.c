/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_threads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 08:25:00 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/09 09:21:34 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static uint8_t  init_thread(t_target *target, t_thread *thread, uint8_t scan)
{
    ft_bzero(thread, sizeof(t_thread));

    thread->results             = NULL;
    thread->src                 = target->src;
    thread->dst                 = target->dst;
    thread->device              = target->device;
    thread->scan                = scan;
    thread->filter.size         = DEFAULT_LEN_FILTER;
    thread->filter.scale        = DEFAULT_LEN_SCALE;

    if (setup_sockfd(thread, scan) != SUCCESS)
        return (FAILURE);

    if (!(thread->filter.buffer = ft_strnew(DEFAULT_LEN_FILTER)))
        return (FAILURE);

    if (generate_filter_tcp_udp(thread) != SUCCESS)
    {
        ft_strdel(&thread->filter.buffer);
        return (FAILURE);
    }

    return (SUCCESS);
}

static uint8_t  reset_thread(t_thread *thread)
{
    thread->results             = NULL;
    thread->filter.size         = DEFAULT_LEN_FILTER;
    thread->filter.scale        = DEFAULT_LEN_SCALE;

    if (!(thread->filter.buffer  = ft_strnew(DEFAULT_LEN_FILTER)))
        return (FAILURE);

    if (generate_filter_tcp_udp(thread) != SUCCESS)
    {
        ft_strdel(&thread->filter.buffer);
        return (FAILURE);
    }

    return (SUCCESS);
}

static uint8_t  create_thread(t_list **threads, t_thread *thread_template)
{

    if (generate_filter_icmp(thread_template) != SUCCESS)
        return (FAILURE);
    if (ft_lstaddback(threads,
            ft_lstnew(thread_template, sizeof(t_thread))) != SUCCESS)
    {
        dprintf(STDERR_FILENO, "ft_nmap: create_thread(): Malloc error\n");
        return (FAILURE);
    }

    return (SUCCESS);
}

static uint8_t  generate_result(t_list **results, t_thread *thread,
                                uint16_t port)
{
    t_result result;

    ft_memset(&result, 0, sizeof(t_result));

    result.port             = port;
    result.scan             = thread->scan;
    result.dst              = thread->dst;
    result.status[S_SYN]    = E_FILTERED;
    result.status[S_NULL]   = E_OPEN_FILTERED;
    result.status[S_ACK]    = E_FILTERED;
    result.status[S_FIN]    = E_OPEN_FILTERED;
    result.status[S_XMAS]   = E_OPEN_FILTERED;
    result.status[S_UDP]    = E_OPEN_FILTERED;

    if (ft_lstaddback(results, ft_lstnew(&result, sizeof(t_result))) != SUCCESS)
    {
        dprintf(STDERR_FILENO, "ft_nmap: generate_result(): Malloc error\n");
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
    if (generate_result(&thread->results, thread, port) == FAILURE)
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

    while(threads && ports)
    {
        t_port *target_port = ports->data;

        if (target_port->type == E_PORT_SINGLE)
        {
            t_thread *thread = threads->data;

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

            while (min_port <= max_port && threads)
            {
                t_thread *thread = threads->data;

                if (add_single_port_handler(thread, min_port) == FAILURE)
                    return (FAILURE);

                threads = threads->next;
                min_port++;
            }

            ports = ports->next;
            continue;
        }

        threads = threads->next;
        ports = ports->next;
    }

    return (generate_filter_src(tmp));
}

uint8_t         generate_threads(t_list **threads, t_target *target,
                                 uint8_t scan)
{
    uint16_t    port_nbr            = 0;
    uint16_t    dispatched_ports    = 0;
    uint16_t    min_port            = 0;
    uint16_t    max_port            = 0;
    uint16_t    start_port          = 0;
    t_thread    template;

    if (init_thread(target, &template, scan) != SUCCESS)
        return (FAILURE);

    for (t_list *current = target->ports; current; current = current->next)
    {
        // If have dispatched all our ports and have leftover, dispatch them
        if (dispatched_ports >= target->port_nbr - target->port_leftover)
            return (dispatch_leftovers(current, *threads, 0));
        else
        {
            t_port *target_port = current->data;

            if (target_port->type == E_PORT_SINGLE)
            {
                port_nbr++;
                dispatched_ports++;

                if (generate_result(&template.results, &template,
                                    target_port->data.port) == FAILURE)
                    return (FAILURE);

                if (generate_filter_port_single(&template,
                        target_port->data.port) == FAILURE)
                    return (FAILURE);

                if (port_nbr == target->port_per_thread)
                {
                    if (create_thread(threads, &template) != SUCCESS)
                            return (FAILURE);
                    port_nbr = 0;
                    if (dispatched_ports
                        < target->port_nbr - target->port_leftover)
                    {
                        if (reset_thread(&template) == FAILURE)
                            return (FAILURE);
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

                    if (generate_result(&template.results,
                                        &template, min_port) == FAILURE)
                        return (FAILURE);

                    if (port_nbr == target->port_per_thread
                        || min_port == max_port)
                    {
                        if (start_port != min_port)
                        {
                            if (generate_filter_port_range(&template,
                                    start_port, min_port) == FAILURE)
                                return (FAILURE);
                        }
                        else
                        {
                            if (generate_filter_port_single(&template,
                                    min_port) == FAILURE)
                                return (FAILURE);
                        }

                        start_port = min_port + 1;

                        if (port_nbr == target->port_per_thread)
                        {
                            if (create_thread(threads, &template) != SUCCESS)
                                return (FAILURE);
                            port_nbr = 0;
                            if (dispatched_ports
                                < target->port_nbr - target->port_leftover)
                            {
                                if (reset_thread(&template) == FAILURE)
                                    return (FAILURE);
                            }
                        }
                    }
                    min_port++;

                    // Dispatch leftover if we have reached the end of the list
                    if (dispatched_ports
                        >= target->port_nbr - target->port_leftover)
                    {
                        return (dispatch_leftovers(current, *threads,
                                                   min_port));
                    }
                }
            }
            if (port_nbr != 0)
                generator_filter_or(&template);
        }
    }

    return (generate_filter_src(*threads));
}
