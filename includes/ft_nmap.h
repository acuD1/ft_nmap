/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:29:25 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/23 19:33:31 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NMAP_H
# define FT_NMAP_H

# include "libft.h"

/* OPTIONS */
# define UNALLOWED_OPT          1ULL << 63
# define H_OPT_ARRAY            "help"
# define P_OPT_ARRAY            "ports"
# define IP_OPT_ARRAY           "ip"
# define S_OPT_ARRAY            "speedup"
# define T_OPT_ARRAY            "scan"
# define ALLOWED_OPT            NULL
# define ALLOWED_OPT_ARG        NULL
# define ALLOWED_OPT_TAB        ((const char *[])   \
                                {                   \
                                    H_OPT_ARRAY,    \
                                    P_OPT_ARRAY,    \
                                    IP_OPT_ARRAY,   \
                                    S_OPT_ARRAY,    \
                                    T_OPT_ARRAY,    \
                                    NULL            \
                                })
# define ALLOWED_OPT_TAB_ARG    ((const char *[])   \
                                {                   \
                                    P_OPT_ARRAY,    \
                                    IP_OPT_ARRAY,   \
                                    S_OPT_ARRAY,    \
                                    T_OPT_ARRAY,    \
                                    NULL            \
                                })
/**/

typedef struct                  s_nmap
{
    t_opts_args                 *opts_args;
}                               t_nmap;

void                            exit_routine(t_nmap *nmap, uint8_t status);
void                            print_unallowed_opt(t_opts_args *opts_args);
void                            print_usage(void);
uint8_t                         set_opts_args(t_nmap *nmap, int argc, char **argv);
void                            free_nmap(t_nmap *nmap);

#endif
