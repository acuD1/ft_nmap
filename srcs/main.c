/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:31:17 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/11 10:45:32 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include <signal.h>

int main(int argc, char *argv[])
{
    t_nmap              nmap;
    struct sigaction    process;

    ft_bzero(&process, sizeof(struct sigaction));

    sigemptyset(&process.sa_mask);

    process.sa_handler = &signal_handler;
    process.sa_flags = (int)SA_RESETHAND;

    sigaction(SIGINT, &process, NULL);

    init_nmap(&nmap, argc, argv);

    if ((nmap.options & DRY_OPT) == 0)
        exec_nmap(&nmap);

    free_nmap(&nmap);

    return (EXIT_SUCCESS);
}
