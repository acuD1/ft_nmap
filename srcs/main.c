/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:31:17 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/25 15:31:06 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

int main(int argc, char *argv[])
{
    t_nmap nmap;

    if (init_nmap(&nmap, argc, argv))
    {
        return (FAILURE);
    }
    free_nmap(&nmap);
    return (SUCCESS);
}
