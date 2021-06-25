/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:29:25 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/25 13:50:14 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NMAP_H
# define FT_NMAP_H

# pragma clang diagnostic ignored "-Wreserved-id-macro"
# define _GNU_SOURCE

# include "libft.h"
# include <netdb.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>

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
    char                        target_ipv4[INET_ADDRSTRLEN];
    uint16_t                    threads;
    uint8_t                     scan;
    char                        pad[1];
}                               t_nmap;

void                            exit_routine(t_nmap *nmap, uint8_t status);
void                            free_nmap(t_nmap *nmap);
void                            getaddrinfo_error_handler(char *arg, int status);
void                            print_unallowed_opt(t_opts_args *opts_args);
void                            print_usage(void);
uint8_t                         resolve_target_ipv4(t_nmap *nmap, char *arg);
uint8_t                         set_opts_args(t_nmap *nmap, int argc, char **argv);

#endif
