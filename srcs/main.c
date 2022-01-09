/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:31:17 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/09 18:26:02 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include <signal.h>

int main(int argc, char *argv[])
{
    t_nmap nmap;
    struct sigaction new_action;

    new_action.sa_handler = signal_handler;
    sigemptyset(&new_action.sa_mask);
    sigaction(SIGINT, &new_action, NULL);

    init_nmap(&nmap, argc, argv);

    if ((nmap.options & DRY_OPT) == 0)
        exec_nmap(&nmap);

    free_nmap(&nmap);

    return (EXIT_SUCCESS);
}
