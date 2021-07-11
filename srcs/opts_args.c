/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 18:42:04 by arsciand          #+#    #+#             */
/*   Updated: 2021/07/11 18:00:25 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static uint8_t  set_opts_args_failure(t_opts_args *opts_args)
{
    free_opts_args(opts_args);
    return (FAILURE);
}

uint8_t         set_opts_args(t_nmap *nmap, int argc, char **argv)
{
    t_opts_args     opts_args;
    t_opts_conf     opts_conf;
    t_opt_set_db    *tmp    = NULL;

    ft_bzero(&opts_args, sizeof(t_opts_conf));
    ft_bzero(&opts_conf, sizeof(t_opts_conf));
    opts_conf.allowed_opt           = ALLOWED_OPT;
    opts_conf.allowed_opt_arg       = ALLOWED_OPT_ARG;
    opts_conf.allowed_opt_tab       = ALLOWED_OPT_TAB;
    opts_conf.allowed_opt_tab_arg   = ALLOWED_OPT_TAB_ARG;

    if (argc == 1)
    {
        print_usage();
        exit_routine(nmap, EXIT_SUCCESS);
    }

    if (ft_get_opts_args(&opts_args, &opts_conf, argc, argv) != SUCCESS)
        return (set_opts_args_failure(&opts_args));

    if (opts_args.args)
    {
        dprintf(STDERR_FILENO, "ft_nmap: extra argument '%s'\n", get_arg(&opts_args.args, POSITION(0))->arg);
        print_usage();
        return (set_opts_args_failure(&opts_args));
    }

    if (opts_args.all & UNALLOWED_OPT)
    {
        print_unallowed_opt(&opts_args);
        return (set_opts_args_failure(&opts_args));
    }

    if ((tmp = get_opt_set_db(&opts_args.opt_set, HELP_STR)) != NULL)
    {
        print_usage();
        exit_routine(nmap, EXIT_SUCCESS);
    }

    if ((tmp = get_opt_set_db(&opts_args.opt_set, IP_STR)) != NULL)
    {
        if (tmp->arg)
        {
            if ((resolve_target_ipv4(nmap, tmp->arg) != SUCCESS))
                return (set_opts_args_failure(&opts_args));
        }
        else
        {
            print_requires_arg_opt_long(tmp->current);
            return (set_opts_args_failure(&opts_args));
        }
    }

    if ((tmp = get_opt_set_db(&opts_args.opt_set, PORTS_STR)) != NULL)
    {
        if (tmp->arg)
        {
            parse_ports(tmp->arg);
        }
        else
        {
            print_requires_arg_opt_long(tmp->current);
            return (set_opts_args_failure(&opts_args));
        }
    }

    if ((tmp = get_opt_set_db(&opts_args.opt_set, THREADS_STR)) != NULL)
    {
        if (tmp->arg)
        {
            if (ft_isnumeric(tmp->arg) != TRUE)
            {
                dprintf(STDERR_FILENO, "ft_nmap: unsupported type '%s' for option '--speedup'\n", tmp->arg);
                return (set_opts_args_failure(&opts_args));
            }
            nmap->threads = (uint16_t)ft_atoi(tmp->arg);
        }
        else
        {
            print_requires_arg_opt_long(tmp->current);
            return (set_opts_args_failure(&opts_args));
        }
    }

    if ((tmp = get_opt_set_db(&opts_args.opt_set, SCAN_STR)) != NULL)
    {
        if (tmp->arg)
        {
            if (set_scan_type(&nmap->scan, tmp->arg) != SUCCESS)
                return (set_opts_args_failure(&opts_args));
        }
        else
        {
            print_requires_arg_opt_long(tmp->current);
            return (set_opts_args_failure(&opts_args));
        }
    }
    else
        nmap->scan = DEFAULT_SCAN;

    // debug_scan_type(nmap->scan);    /* DEBUG */
    // debug_opts_args(&opts_args);    /* DEBUG */
    free_opts_args(&opts_args);
    return (SUCCESS);
}
