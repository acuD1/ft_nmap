/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:29:25 by arsciand          #+#    #+#             */
/*   Updated: 2021/12/18 14:16:51 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NMAP_H
# define FT_NMAP_H

#include <pthread.h>
# pragma clang diagnostic ignored "-Wreserved-id-macro"
# define _GNU_SOURCE

# include "libft.h"


# include <arpa/inet.h>
# include <netdb.h>
# include <stdbool.h>
# include <netinet/tcp.h>
# include <netinet/ip.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <errno.h>
# include <stdbool.h>
# include <ifaddrs.h>
# include <linux/if_link.h>
# include <net/if.h>

# define errno                  (*__errno_location ())

/* DEFAULTS */
# define DEFAULT_THREADS        1
# define DEFAULT_SCAN           0x0040

/* OPTIONS */
# define POSITION(x)            x
# define UNALLOWED_OPT          1ULL << 63
# define HELP_STR               "help"
# define PORTS_STR              "ports"
# define IP_STR                 "ip"
# define THREADS_STR            "speedup"
# define SCAN_STR               "scan"
# define FILE_STR               "file"
# define DRY_STR                "dry-run"
# define ALLOWED_OPT            NULL
# define ALLOWED_OPT_ARG        NULL
# define ALLOWED_OPT_TAB        ((const char *[])   \
                                {                   \
                                    HELP_STR,       \
                                    PORTS_STR,      \
                                    IP_STR,         \
                                    THREADS_STR,    \
                                    SCAN_STR,       \
                                    FILE_STR,       \
                                    DRY_STR,       \
                                    NULL            \
                                })
# define ALLOWED_OPT_TAB_ARG    ((const char *[])   \
                                {                   \
                                    PORTS_STR,      \
                                    IP_STR,         \
                                    THREADS_STR,    \
                                    SCAN_STR,       \
                                    FILE_STR,       \
                                    NULL            \
                                })
/**/

/* SCAN TYPES */
# define WRONG_FORMAT           0x0001
# define WRONG_TYPE             0x0002
# define SCAN_SYN               0x0001
# define SCAN_SYN_STR           "SYN"
# define SCAN_NULL              0x0002
# define SCAN_NULL_STR          "NULL"
# define SCAN_ACK               0x0004
# define SCAN_ACK_STR           "ACK"
# define SCAN_FIN               0x0008
# define SCAN_FIN_STR           "FIN"
# define SCAN_XMAS              0x0010
# define SCAN_XMAS_STR          "XMAS"
# define SCAN_UDP               0x0020
# define SCAN_UDP_STR           "UDP"
# define ALLOWED_SCAN_TYPE      ((const char *[])   \
                                {                   \
                                    SCAN_SYN_STR,   \
                                    SCAN_NULL_STR,  \
                                    SCAN_ACK_STR,   \
                                    SCAN_FIN_STR,   \
                                    SCAN_XMAS_STR,  \
                                    SCAN_UDP_STR,   \
                                    NULL            \
                                })
/**/

/* OPTIONS */

# define DRY_OPT 0x01

# define RANGE_START            0
# define RANGE_END              1
# define UINT

/* LEXER */
typedef enum                    e_lexer_state{
    L_BASE,
    L_LBRACE,
    L_RBRACE,
    L_PARENT,
    L_EXCLUDE,
    L_SET_SINGLE,
    L_SET_START,
    L_SET_RANGE,
    L_SET_END,
    L_TOKENIZE,
    L_OUT,
    L_FINISH,
    L_FAILURE,
    L_ERROR
}                               t_lexer_state;

typedef enum                    e_port_type
{
    E_PORT_UNSET,
    E_PORT_SINGLE,
    E_PORT_RANGE
}                               e_port;

typedef union                   u_port_data
{
    uint16_t                    port;
    uint16_t                    range[2];
}                               t_port_data;

typedef struct                  s_port
{
    e_port                      type;
    t_port_data                 data;
}                               t_port;

typedef struct                  s_lexer
{
    t_port                      tmp_port;
    char                        *source;
    t_list                      *result;
    t_vector                    *vector;
    t_lexer_state               state;
    uint8_t                     _padding[4];
}                               t_lexer;

typedef struct                  s_packet
{
    uint32_t                    saddr;
	uint32_t                    daddr;
	uint16_t                    tcp_len;
	uint8_t                     tos;
	uint8_t                     protocol;
    struct tcphdr               tcphdr;
}                               t_packet;

/*
** A target is composed of:
**      - destination ip
**      - list of ports
** Each target must be scanned separately
** Multi target scan can only occur when reading targets from file
** Port parser is in charge of validating that the list of ports is valid
** (Less than 1024)
*/
typedef struct                  s_target
{
    struct sockaddr_storage     dest;
    uint8_t                     p_nbr;          // Number of ports to scan
    t_list                      *ports;         // list of t_port(with ranges)
}                               t_target;

/*
** A thread will iterate over its list of ports, and scan each.
** Threads are generated per targets.
** There cannot be more than 250 threads per target
** The list of ports is a list of int.
*/
typedef struct                  s_thread
{
    t_list                      *ports;         // list of uint8_t(unique ports)
    char                        _padding[6];
    pthread_t                   id;
    struct sockaddr_storage     src;
    struct sockaddr_storage     dst;
}                               t_thread;

typedef struct                  s_scan
{
    uint8_t port;

} t_scan;

typedef struct                  s_nmap
{
    t_list                      *targets;
    uint8_t                     scan;
    uint8_t                     options;
    char                        pad[6];
    struct sockaddr_storage     src;
}                               t_nmap;

void                            init_nmap(t_nmap *nmap, int ac, char **av);
void                            exit_routine(t_nmap *nmap, uint8_t status);
void                            free_nmap(t_nmap *nmap);
void                            getaddrinfo_error_handler(char *arg, int status);
uint8_t                         set_scan_type(uint8_t *scan, const char *arg);
uint8_t                         resolve_target_ipv4(t_target *target_data, char *arg);
uint8_t                         set_opts_args(t_nmap *nmap, int argc, char **argv);
void                            exec_nmap(t_nmap *nmap);
uint8_t                         resolve_local_ipv4(t_nmap *nmap);
uint16_t                        in_cksum(void *buffer, size_t len);
int                             send_target(void *context, void* data);
int scan_target(void *data, void *context);

/* Print */
void                            print_target(void *data);
void                            print_source_ip(t_nmap *nmap);
void                            print_requires_arg_opt_long(char *current);
void                            print_unallowed_opt(t_opts_args *opts_args);
void                            print_usage(void);

/* LEXER */
t_list                          *parse_ports(char *ports);
void                            process_base(t_lexer *lexer);
bool                            is_set_state(t_lexer *lexer);
bool                            is_source_finished(t_lexer *lexer);
bool                            is_exit_state(t_lexer *lexer);

/* DEBUG */
void                            debug_scan_type(uint8_t scan);
void                            display_token(void *data);
void                            debug_ports(t_list *ports);
void                            debug_targets(void *data);
void                            debug_threads(t_nmap *nmap);

/* DEV */

#endif
