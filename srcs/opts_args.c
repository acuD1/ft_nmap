/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 18:42:04 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/25 17:09:58 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static uint8_t scan_args_parser(const char *arg)
{
    char        **split                 = NULL;
    // int8_t  scan    = 0;

    split = ft_strsplit(arg, ",");
    for (size_t i = 0; split[i]; i++)
    {
        printf("[%zu]|%s|\n", i, split[i]);
    }
    return (SUCCESS);
}

uint8_t set_opts_args(t_nmap *nmap, int argc, char **argv)
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
    {
        free_opts_args(&opts_args);
        return (FAILURE);
    }

    if (opts_args.all & UNALLOWED_OPT)
    {
        print_unallowed_opt(&opts_args);
        free_opts_args(&opts_args);
        return (FAILURE);
    }

    if ((tmp = get_opt_set_db(&opts_args.opt_set, IP_OPT_ARRAY)) != NULL)
    {
        if (tmp->arg)
        {
            if ((resolve_target_ipv4(nmap, tmp->arg) != SUCCESS))
            {
                free_opts_args(&opts_args);
                return (FAILURE);
            }
        }
        else
        {
            print_requires_arg_opt_long(tmp->current);
            free_opts_args(&opts_args);
            return (FAILURE);
        }
    }

    if ((tmp = get_opt_set_db(&opts_args.opt_set, P_OPT_ARRAY)) != NULL)
    {
        if (tmp->arg)
        {
            parse_ports(tmp->arg);
        }
    }

    if ((tmp = get_opt_set_db(&opts_args.opt_set, S_OPT_ARRAY)) != NULL)
    {
        if (tmp->arg)
        {
            nmap->threads = (uint16_t)ft_atoi(tmp->arg);
        }
        else
        {
            print_requires_arg_opt_long(tmp->current);
            free_opts_args(&opts_args);
            return (FAILURE);
        }
    }

    if ((tmp = get_opt_set_db(&opts_args.opt_set, T_OPT_ARRAY)) != NULL)
    {
        if (tmp->arg)
        {
            if ((nmap->scan = scan_args_parser(tmp->arg)) != SUCCESS)
            {
                free_opts_args(&opts_args);
                return (FAILURE);
            }
        }
    }

    // debug_opts_args(&opts_args); /* DEBUG */
    free_opts_args(&opts_args);
    return (SUCCESS);
}
