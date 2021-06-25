/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scan_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 18:32:00 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/25 19:28:10 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void            debug_scan_type(uint8_t scan)
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

static uint8_t  get_scan_type_failure(char **tab, char *scan, uint8_t type)
{
    if (type & WRONG_FORMAT)
    {
        dprintf(STDERR_FILENO,
            "ft_nmap: wrong format '%s' for option '--scan'\n", scan);
    }
    if (type & WRONG_TYPE)
    {
        dprintf(STDERR_FILENO,
            "ft_nmap: unsupported type '%s' for option '--scan'\n", scan);
    }
    ft_tabdel(&tab);
    return (FAILURE);
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
        print_requires_arg_opt_long(SCAN_STR);
        ft_tabdel(&split);
        return (FAILURE);
    }
    for (size_t i = 0; split[i]; i++)
    {
        for (size_t j = 0; split[i][j]; j++)
        {
            if (ft_isalpha(split[i][j]) == FALSE)
                return (get_scan_type_failure(split, split[i], WRONG_FORMAT));
        }
        if (is_scan_type_found(split[i]) == TRUE)
            get_scan_type_mask(scan, split[i]);
        else
            return (get_scan_type_failure(split, split[i], WRONG_TYPE));
    }
    ft_tabdel(&split);
    return (SUCCESS);
}
