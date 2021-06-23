/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:31:17 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/23 19:26:23 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

int     main(int argc, char *argv[])
{
    t_nmap  nmap;

    ft_bzero(&nmap, sizeof(t_nmap));

    if (set_opts_args(&nmap, argc, argv) != SUCCESS)
        exit_routine(&nmap, FAILURE);

    /* DEBUG */
    debug_opts_args(nmap.opts_args);

    free_nmap(&nmap);
    return (EXIT_SUCCESS);
}
