/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ports.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:21:28 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/25 21:26:04 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include <stdio.h>
#include <stdbool.h>

uint8_t init_lexer(t_lexer *lexer, char *ports)
{
    lexer->result = NULL;
    lexer->state = L_BASE;
    lexer->vector = vct_new(DEFAULT_VECTOR_SIZE);
    lexer->source = ports;
    lexer->tmp_port.type = E_PORT_UNSET;
    lexer->tmp_port.data.port = 0;
    return (EXIT_SUCCESS);
}

bool is_source_finished(t_lexer *lexer)
{
    return (lexer->source[0] == '\0'? true : false);
}

void process_base(t_lexer *lexer)
{
    if (lexer->vector->buffer[0] == '\0')
    {
        if(ft_isdigit(lexer->source[0]))
            vct_add(lexer->vector, lexer->source[0]);
        else if (lexer->source[0] == '[')
            lexer->state = L_LBRACE;
        else if (lexer->source[0] == '(')
            lexer->state = L_PARENT;
        else if (lexer->source[0] == '~')
            lexer->state = L_EXCLUDE;
    }
}


void process_lexer(t_lexer *lexer)
{
    if (is_source_finished(lexer))
        lexer->state = L_OUT;
    else if (lexer->state == L_BASE)
        process_base(lexer);
}

void out_lexer(t_lexer *lexer)
{
    lexer->state = L_FINISH;
}

uint8_t parse_ports(char *ports)
{
    t_lexer lexer;

    init_lexer(&lexer, ports);
    while(lexer.state != L_FINISH)
        lexer.state == L_OUT ? out_lexer(&lexer) : process_lexer(&lexer);
    printf("Ports string: %s", ports);
    return (EXIT_SUCCESS);
}
