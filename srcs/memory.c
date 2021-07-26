/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 18:43:16 by arsciand          #+#    #+#             */
/*   Updated: 2021/07/26 14:15:16 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void __attribute__ ((noreturn)) exit_routine(t_nmap *nmap, uint8_t status)
{
    free_nmap(nmap);
    exit(status);
}

void    free_nmap(t_nmap *nmap)
{
    ft_lstdel(&nmap->target, del_target);
}
