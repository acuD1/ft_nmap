/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:31:17 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/24 18:21:23 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

int     main(int argc, char *argv[])
{
    t_nmap      nmap;

    ft_bzero(&nmap, sizeof(t_nmap));
    ft_bzero(&nmap.target_ipv4, sizeof(nmap.target_ipv4));

    if (set_opts_args(&nmap, argc, argv) != SUCCESS)
        exit_routine(&nmap, FAILURE);

    free_nmap(&nmap);
    return (0);
}
