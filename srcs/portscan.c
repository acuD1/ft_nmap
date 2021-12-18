/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portscan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:27:15 by cempassi          #+#    #+#             */
/*   Updated: 2021/12/18 18:36:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include "list.h"
#include <stdio.h>
#include <strings.h>

// - scan_target
//  - scan_thread
//    - scan_port

static void init_thread(t_nmap *nmap, t_target *target, t_thread *thread)
{
    thread->ports = NULL;
    thread->id = 0;
    thread->src = nmap->src;
    thread->dst = target->dst;
}

static void reset_thread(t_thread *thread)
{
    thread->ports = NULL;
}

static uint8_t create_thread(t_list **threads, t_thread *thread_template)
{
    if (!ft_lstaddback(threads, ft_lstnew(thread_template, sizeof(t_thread))))
    {
        printf("[ERROR] Thread Creation FAILURE\n");
        return (FAILURE);
    }
    reset_thread(thread_template);
    return (SUCCESS);
}

static uint8_t add_port(t_list **ports, uint16_t port)
{
    if (!ft_lstaddback(ports, ft_lstnew(&port, sizeof(uint16_t))))
    {
        printf("[ERROR] single port FAILURE\n");
        return (FAILURE);
    }
    return (SUCCESS);
}

static void set_range(t_port *target, uint16_t *min_port, uint16_t *max_port)
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

static t_list *generate_threads(t_target *target, t_thread *thread_template)
{
    t_list * threads;
    uint16_t port_nbr = 0;
    uint16_t min_port;
    uint16_t max_port;

    threads = NULL;

    for (t_list *current = target->ports; current; current = current->next)
    {
        t_port *target_port = current->data;
        if (target_port->type == E_PORT_SINGLE)
        {
            port_nbr++;
            if (add_port(&thread_template->ports, target_port->data.port)
                == FAILURE)
                return (NULL);
        }
        else
        {
            set_range(target_port, &min_port, &max_port);
            while (min_port <= max_port)
            {
                port_nbr++;
                if (add_port(&thread_template->ports, min_port) == FAILURE)
                    return (NULL);
                if (port_nbr == target->port_per_thread)
                {
                    if (create_thread(&threads, thread_template) == SUCCESS)
                        port_nbr = 0;
                    else
                        return (NULL);
                }
                min_port++;
            }
        }

        if (port_nbr == target->port_per_thread)
        {
            if (create_thread(&threads, thread_template) == SUCCESS)
                port_nbr = 0;
            else
                return (NULL);
        }
    }
    return (threads);
}

int scan_target(void *data, void *context)
{
    t_target *target;
    t_nmap *  nmap;
    t_list *  threads;
    t_thread  thread;

    nmap = context;
    target = data;
    threads = NULL;
    print_target(target);

    // Thread repartition must happend here
    init_thread(nmap, target, &thread); // Set base values
    if ((threads = generate_threads(target, &thread)) == NULL)
        return (FAILURE);
    ft_lstiter(threads, print_thread);

    ft_lstdel(&threads, delete_thread);
    return (SUCCESS);
}
