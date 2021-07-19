/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:30:35 by arsciand          #+#    #+#             */
/*   Updated: 2021/07/19 12:07:41 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include "other.h"
# include "memory.h"
# include "str.h"
# include "list.h"
# include "vector.h"

# define BUFF_SIZE  4096
# define TRUE       1
# define FALSE      0
# define SUCCESS    0
# define FAILURE    2

/* ft_get_opts_args */
typedef struct      s_opt_set_db
{
    char            *current;
    char            *arg;
    char            pad[4];
    int             argc;
}                   t_opt_set_db;

typedef struct      s_args_db
{
    char            *arg;
    char            pad[4];
    int             argc;
}                   t_args_db;

typedef struct      s_opts_args
{
    t_list          *opt_set;
    t_list          *args;
    uint64_t        all;
    char            *invalid;
    char            pad[4];
    int             argc;
}                   t_opts_args;

typedef struct      s_opts_conf
{
    const char      *allowed_opt;
    const char      *allowed_opt_arg;
    const char      **allowed_opt_tab;
    const char      **allowed_opt_tab_arg;
}                   t_opts_conf;

uint8_t             ft_get_opts_args(t_opts_args *opts_args, t_opts_conf *opts_conf, int argc, char **argv);
void                debug_opts_args(t_opts_args *opts_args);
void                free_opts_args(t_opts_args *opts_args);
t_args_db           *get_arg(t_list **alist_args, int argc);
t_opt_set_db        *get_opt_set_db(t_list **alist_opt_set, char *to_find);

#endif
