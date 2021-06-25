/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:29:25 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/25 16:23:24 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NMAP_H
#define FT_NMAP_H

#pragma clang diagnostic ignored "-Wreserved-id-macro"
#define _GNU_SOURCE

#include "libft.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

/* DEFAULTS */
#define DEFAULT_THREADS 1
#define DEFAULT_SCAN 0x01

/* OPTIONS */
#define UNALLOWED_OPT 1ULL << 63
#define H_OPT_ARRAY "help"
#define P_OPT_ARRAY "ports"
#define IP_OPT_ARRAY "ip"
#define S_OPT_ARRAY "speedup"
#define T_OPT_ARRAY "scan"
#define ALLOWED_OPT NULL
#define ALLOWED_OPT_ARG NULL
#define ALLOWED_OPT_TAB                                                        \
    ((const char *[]){ H_OPT_ARRAY, P_OPT_ARRAY, IP_OPT_ARRAY, S_OPT_ARRAY,    \
                       T_OPT_ARRAY, NULL })
#define ALLOWED_OPT_TAB_ARG                                                    \
    ((const char *[]){ P_OPT_ARRAY, IP_OPT_ARRAY, S_OPT_ARRAY, T_OPT_ARRAY,    \
                       NULL })
/**/

#define RANGE_START 0
#define RANGE_END 1

typedef enum e_port_type
{
    E_PORT_SINGLE,
    E_PORT_RANGE
}           e_port;

typedef union   u_port_data
{
    uint8_t port;
    uint8_t range[2];
}               t_port_data;

typedef struct  s_port
{
    e_port      type;
    t_port_data data;
}               t_port;

typedef struct  s_nmap
{
    char     target_ipv4[INET_ADDRSTRLEN];
    uint16_t threads;
    uint8_t  scan;
    t_list   *ports;
    char     pad[1];
}               t_nmap;

int     init_nmap(t_nmap *nmap, int ac, char **av);
void    exit_routine(t_nmap *nmap, uint8_t status);
void    free_nmap(t_nmap *nmap);
void    getaddrinfo_error_handler(char *arg, int status);
void    print_unallowed_opt(t_opts_args *opts_args);
void    print_usage(void);
uint8_t resolve_target_ipv4(t_nmap *nmap, char *arg);
uint8_t set_opts_args(t_nmap *nmap, int argc, char **argv);
int     parse_ports(char *ports);

#endif
