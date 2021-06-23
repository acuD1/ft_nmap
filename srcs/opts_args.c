/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 18:42:04 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/23 19:34:59 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

uint8_t set_opts_args(t_nmap *nmap, int argc, char **argv)
{
    t_opts_conf     opts_conf;

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

    if (!(nmap->opts_args = ft_get_opts_args(argc, argv, &opts_conf)))
        return (FAILURE);

    if (nmap->opts_args->all & UNALLOWED_OPT)
    {
        print_unallowed_opt(nmap->opts_args);
        return (FAILURE);
    }

    return (SUCCESS);
}
