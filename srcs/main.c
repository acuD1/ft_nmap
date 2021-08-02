/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:31:17 by arsciand          #+#    #+#             */
/*   Updated: 2021/08/02 10:04:04 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

int main(int argc, char *argv[])
{
    t_nmap nmap;

    init_nmap(&nmap, argc, argv);

    if ((nmap.options & DRY_OPT) == 0)
        exec_nmap(&nmap);

    free_nmap(&nmap);

    return (EXIT_SUCCESS);
}
