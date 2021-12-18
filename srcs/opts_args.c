/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 18:42:04 by arsciand          #+#    #+#             */
/*   Updated: 2021/12/18 16:06:01 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static uint8_t set_opts_args_failure(t_opts_args *opts_args)
{
    free_opts_args(opts_args);
    return (FAILURE);
}

static uint8_t get_threads(t_nmap *nmap, t_opts_args *opts, t_opt_set_db *tmp)
{
    if (ft_isnumeric(tmp->arg) != TRUE)
    {
        dprintf(STDERR_FILENO,
                "ft_nmap: unsupported type '%s' for option '--speedup'\n",
                tmp->arg);
        return (set_opts_args_failure(opts));
    }
    // FIXME: Protection thread max = 255
    nmap->threads = (uint8_t)ft_atoi(tmp->arg);
    return (SUCCESS);
}

static uint8_t get_scan(t_nmap *nmap, t_opts_args *opts, t_opt_set_db *tmp)
{
    if (set_scan_type(&nmap->scan, tmp->arg) != SUCCESS)
        return (set_opts_args_failure(opts));
    return (SUCCESS);
}

static void sum_ports(void *data, void *acc)
{
    t_port *  port;
    uint16_t *port_number;

    port = data;
    port_number = acc;
    if (port->type == E_PORT_SINGLE)
        *port_number += 1;
    else
        *port_number += port->data.range[1] - port->data.range[0] + 1;
}

static uint8_t count_ports(t_nmap *nmap, t_target *target)
{
    ft_lstfold(target->ports, &(target->port_nbr), sum_ports);
    if (target->port_nbr > 1024)
        return (FAILURE);
    target->port_per_thread = target->port_nbr / nmap->threads;
    target->port_leftover = target->port_nbr % nmap->threads;
    printf("port_number: %hu | port_per_thread: %hu | port_leftover: %hu\n",
           target->port_nbr, target->port_per_thread, target->port_leftover);
    return (SUCCESS);
}

static uint8_t get_target_data_from_line(t_nmap *nmap, char *line,
                                         t_opts_args *opts)
{
    t_target target;
    t_list * node;
    char **  tab;

    ft_bzero(&target, sizeof(t_target));
    node = NULL;
    tab = NULL;
    if ((tab = ft_strsplit(line, ":")) == NULL)
        return (FAILURE);
    if (ft_tablen(tab) != 2)
        return (FAILURE);
    if ((resolve_target_ipv4(&target, tab[0]) != SUCCESS))
        return (set_opts_args_failure(opts));
    if ((target.ports = parse_ports(tab[1])) == NULL)
        return (set_opts_args_failure(opts));
    if (count_ports(nmap, &target) == FAILURE)
        return (set_opts_args_failure(opts));
    if ((node = ft_lstnew(&target, sizeof(t_target))) == NULL)
    {
        return (set_opts_args_failure(opts));
    }
    ft_lstaddback(&nmap->targets, node);
    ft_freetab(&tab);
    return (SUCCESS);
}

static uint8_t get_ip_file(t_nmap *nmap, t_opts_args *opts, t_opt_set_db *tmp)
{
    int   fd;
    char *line;

    fd = 0;
    line = NULL;
    if ((tmp = get_opt_set_db(&opts->opt_set, IP_STR)))
        return (FAILURE);
    if ((tmp = get_opt_set_db(&opts->opt_set, PORTS_STR)))
        return (FAILURE);
    if ((tmp = get_opt_set_db(&opts->opt_set, FILE_STR)) == NULL)
        return (FAILURE);
    else
    {
        if ((fd = open(tmp->arg, O_RDONLY)) == -1)
            return (FAILURE);
        while (ft_getdelim(fd, &line, '\n') == 1)
        {
            if (get_target_data_from_line(nmap, line, opts) == FAILURE)
                return (FAILURE);
            ft_strdel(&line);
        }
        if (line)
            ft_strdel(&line);
    }
    return (SUCCESS);
}

static uint8_t get_ip_cli(t_nmap *nmap, t_opts_args *opts, t_opt_set_db *tmp)
{
    t_target target;
    t_list * node;

    ft_bzero(&target, sizeof(t_target));
    node = NULL;
    if ((tmp = get_opt_set_db(&opts->opt_set, IP_STR)) != NULL)
    {
        if ((resolve_target_ipv4(&target, tmp->arg) != SUCCESS))
            return (set_opts_args_failure(opts));
    }
    else
        return (FAILURE);

    if ((tmp = get_opt_set_db(&opts->opt_set, PORTS_STR)) != NULL)
    {
        if ((target.ports = parse_ports(tmp->arg)) == NULL)
        {
            return (set_opts_args_failure(opts));
        }
    }
    // FIXME: Default ports scan must run with the range 1-1024.
    if (count_ports(nmap, &target) == FAILURE)
    {
        return (set_opts_args_failure(opts));
    }

    if ((node = ft_lstnew(&target, sizeof(t_target))) == NULL)
    {
        return (set_opts_args_failure(opts));
    }
    ft_lstaddback(&nmap->targets, node);
    return (SUCCESS);
}

static int validate_opt(void *data, void *context)
{
    t_opt_set_db *option;
    t_opts_conf * config;

    option = data;
    config = context;
    for (int i = 0; config->allowed_opt_tab_arg[i] != NULL; i++)
    {
        if (ft_strequ(option->current, config->allowed_opt_tab_arg[i]))
        {
            if (option->arg == NULL)
            {
                print_requires_arg_opt_long(option->current);
                return (FAILURE);
            }
            return (SUCCESS);
        }
    }
    return (SUCCESS);
}

uint8_t set_opts_args(t_nmap *nmap, int argc, char **argv)
{
    t_opts_args   opts_args;
    t_opts_conf   opts_conf;
    t_opt_set_db *tmp = NULL;

    ft_bzero(&opts_args, sizeof(t_opts_conf));
    ft_bzero(&opts_conf, sizeof(t_opts_conf));
    opts_conf.allowed_opt = ALLOWED_OPT;
    opts_conf.allowed_opt_arg = ALLOWED_OPT_ARG;
    opts_conf.allowed_opt_tab = ALLOWED_OPT_TAB;
    opts_conf.allowed_opt_tab_arg = ALLOWED_OPT_TAB_ARG;

    if (argc == 1)
    {
        print_usage();
        exit_routine(nmap, EXIT_SUCCESS);
    }

    if (ft_get_opts_args(&opts_args, &opts_conf, argc, argv) != SUCCESS)
        return (set_opts_args_failure(&opts_args));

    if (opts_args.args)
    {
        dprintf(STDERR_FILENO, "ft_nmap: extra argument '%s'\n",
                get_arg(&opts_args.args, POSITION(0))->arg);
        print_usage();
        return (set_opts_args_failure(&opts_args));
    }

    if (opts_args.all & UNALLOWED_OPT)
    {
        print_unallowed_opt(&opts_args);
        return (set_opts_args_failure(&opts_args));
    }

    if (ft_lstiter_ctx(opts_args.opt_set, &opts_conf, validate_opt) == FAILURE)
    {
        set_opts_args_failure(&opts_args);
        exit_routine(nmap, EXIT_SUCCESS);
    }

    if ((tmp = get_opt_set_db(&opts_args.opt_set, HELP_STR)) != NULL)
    {
        print_usage();
        exit_routine(nmap, EXIT_SUCCESS);
    }

    if ((tmp = get_opt_set_db(&opts_args.opt_set, DRY_STR)) != NULL)
    {
        nmap->options |= DRY_OPT;
    }

    if ((tmp = get_opt_set_db(&opts_args.opt_set, THREADS_STR)) != NULL)
    {
        if (get_threads(nmap, &opts_args, tmp) == FAILURE)
            exit_routine(nmap, EXIT_SUCCESS);
    }

    if ((tmp = get_opt_set_db(&opts_args.opt_set, SCAN_STR)) != NULL)
    {
        if (get_scan(nmap, &opts_args, tmp) == FAILURE)
            exit_routine(nmap, EXIT_SUCCESS);
    }
    else
        nmap->scan = DEFAULT_SCAN; // Temporay fix

    if ((tmp = get_opt_set_db(&opts_args.opt_set, FILE_STR)) != NULL)
    {
        if (get_ip_file(nmap, &opts_args, tmp) == FAILURE)
            exit_routine(nmap, EXIT_SUCCESS);
    }
    else
    {
        if (get_ip_cli(nmap, &opts_args, tmp) == FAILURE)
            exit_routine(nmap, EXIT_SUCCESS);
    }

    // debug_scan_type(nmap->scan);    /* DEBUG */
    // debug_opts_args(&opts_args);    /* DEBUG */
    free_opts_args(&opts_args);
    return (SUCCESS);
}
