/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:30:22 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/25 14:10:19 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void    print_usage(void)
{
    dprintf(STDOUT_FILENO, "%s%s",
        "ft_nmap [--help] [--ports [NOMBRE/PLAGE]]",
        " --ip ADRESSE IP [--speedup [NOMBRE]] [--scan [TYPE]]\n");
}

void     print_unallowed_opt(t_opts_args *opts_args)
{
    if (opts_args->invalid)
        fprintf(stderr,
            "ft_nmap: unrecognized option '--%s'\n", opts_args->invalid);
    else
        fprintf(stderr,
            "ft_nmap: invalid option -- '%c'\n", (char)(opts_args->all % 128));
    free_opts_args(opts_args);
}
