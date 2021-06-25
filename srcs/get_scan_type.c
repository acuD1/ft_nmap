/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scan_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 18:32:00 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/25 18:36:47 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void     debug_scan_type(uint8_t scan)
{
    dprintf(STDOUT_FILENO,
        "\n>> SCAN_TYPE DEBUG\n\n%s%s\n%s%s\n%s%s\n%s%s\n%s%s\n%s%s\n\n",
        "SYN    -> ", scan & SCAN_SYN ? "OK" : "NO",
        "NULL   -> ", scan & SCAN_NULL ? "OK" : "NO",
        "ACK    -> ", scan & SCAN_ACK ? "OK" : "NO",
        "FIN    -> ", scan & SCAN_FIN ? "OK" : "NO",
        "XMAS   -> ", scan & SCAN_XMAS ? "OK" : "NO",
        "UDP    -> ", scan & SCAN_UDP ? "OK" : "NO"
        );
}

static uint8_t  is_scan_type_found(const char *type)
{
    for (size_t i = 0; ALLOWED_SCAN_TYPE[i]; i++)
        if (ft_strequ(ALLOWED_SCAN_TYPE[i], type) == TRUE)
            return (TRUE);
    return (FALSE);
}

static void     get_scan_type_mask(uint8_t *scan, const char *type)
{
    if (ft_strequ(type, SCAN_SYN_STR))
        *scan |= SCAN_SYN;
    else if (ft_strequ(type, SCAN_NULL_STR))
        *scan |= SCAN_NULL;
    else if (ft_strequ(type, SCAN_ACK_STR))
        *scan |= SCAN_ACK;
    else if (ft_strequ(type, SCAN_FIN_STR))
        *scan |= SCAN_FIN;
    else if (ft_strequ(type, SCAN_UDP_STR))
        *scan |= SCAN_UDP;
    else
        *scan |= SCAN_XMAS;
}

uint8_t         get_scan_type(uint8_t *scan, const char *arg)
{
    char    **split = NULL;

    if (!(split = ft_strsplit(arg, ",")))
        return (FAILURE);
    if (!split[0])
    {
        ft_tabdel(&split);
        print_requires_arg_opt_long(T_OPT_ARRAY);
        return (FAILURE);
    }
    for (size_t i = 0; split[i]; i++)
    {
        for (size_t j = 0; split[i][j]; j++)
        {
            if (ft_isalpha(split[i][j]) == FALSE)
            {
                printf("Bad format |%s|\n", split[i]);
                ft_tabdel(&split);
                return (FAILURE);
            }
        }
        if (is_scan_type_found(split[i]) == TRUE)
            get_scan_type_mask(scan, split[i]);
        else
        {
            printf("Wrong type |%s|\n", split[i]);
            ft_tabdel(&split);
            return (FAILURE);
        }
    }
    ft_tabdel(&split);
    return (SUCCESS);
}
