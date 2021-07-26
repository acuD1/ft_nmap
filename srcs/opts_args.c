/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 18:42:04 by arsciand          #+#    #+#             */
/*   Updated: 2021/07/23 11:33:37 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

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
    nmap->threads = (uint16_t)ft_atoi(tmp->arg);
    return (SUCCESS);
}

static uint8_t get_scan(t_nmap *nmap, t_opts_args *opts, t_opt_set_db *tmp)
{
    if (set_scan_type(&nmap->scan, tmp->arg) != SUCCESS)
        return (set_opts_args_failure(opts));
    return (SUCCESS);
}

static uint8_t get_ip_file(t_nmap *nmap, t_opts_args *opts, t_opt_set_db *tmp)
{
    if (tmp->arg)
    {
        printf("Load targets from file\n");
        //False Line, carefull
        nmap->target = opts->opt_set;
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

    if ((node = ft_lstnew(&target, sizeof(t_target))) == NULL)
    {
        return (set_opts_args_failure(opts));
    }
    ft_lstaddback(&nmap->target, node);
    return (SUCCESS);
}

static int validate_opt(void *context, void *data)
{
    t_opt_set_db *option;
    t_opts_conf  *config;

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
