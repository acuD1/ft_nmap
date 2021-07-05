/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ports.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:21:28 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/26 17:16:49 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include "str.h"
#include "vector.h"
#include <stdio.h>
#include <limits.h>

static uint8_t init_lexer(t_lexer *lexer, char *ports)
{
    lexer->result = NULL;
    lexer->state = L_BASE;
    if ((lexer->vector = vct_new(DEFAULT_VECTOR_SIZE)) == NULL)
    {
        lexer->state = L_FAILURE;
        return (FAILURE);
    }
    lexer->source = ports;
    lexer->tmp_port.type = E_PORT_UNSET;
    lexer->tmp_port.data.port = 0;
    return (SUCCESS);
}

static void set_port(t_lexer *lexer)
{
    uint16_t *port;
    uint32_t  check;

    port = NULL;
    if (lexer->state == L_SET_SINGLE)
        port = &lexer->tmp_port.data.port;
    else if (lexer->state == L_SET_START)
        port = &lexer->tmp_port.data.range[RANGE_START];
    else if (lexer->state == L_SET_END)
        port = &lexer->tmp_port.data.range[RANGE_END];
    check = (uint32_t)ft_atoi(lexer->vector->buffer);
    if (check > USHRT_MAX)
    {
        lexer->state = L_ERROR;
        dprintf(STDERR_FILENO, "Port trop grand");
    }
    else
    {
        *port = (uint16_t)check;
        if (lexer->state == L_SET_SINGLE || lexer->state == L_SET_END)
            lexer->state = L_TOKENIZE;
        else if (lexer->state == L_SET_START)
            lexer->state = L_RRANGE;
    }
}

static void tokenizer(t_lexer *lexer)
{
    t_list *node;

    if ((node = ft_lstnew(&lexer->tmp_port, sizeof(t_port))) == NULL)
    {
        lexer->state = L_FAILURE;
        return;
    }
    ft_lstaddback(&lexer->result, node);
    ft_bzero(&lexer->tmp_port, sizeof(t_port));
    ft_strclr(lexer->vector->buffer);
    lexer->tmp_port.type = E_PORT_UNSET;
    lexer->state = L_BASE;
}

static void process_lexer(t_lexer *lexer)
{
    if (is_source_finished(lexer))
        lexer->state = L_OUT;
    else if (lexer->state == L_BASE)
        process_base(lexer);
    else if (is_set_state(lexer))
        set_port(lexer);
    else if (lexer->state == L_TOKENIZE)
        tokenizer(lexer);
}

static void out_lexer(t_lexer *lexer)
{
    vct_del(&lexer->vector);
    lexer->state = L_FINISH;
}

uint8_t parse_ports(char *ports)
{
    t_lexer lexer;

    if (init_lexer(&lexer, ports) == FAILURE)
        return (FAILURE);
    while (is_exit_state(&lexer) == false)
        lexer.state == L_OUT ? out_lexer(&lexer) : process_lexer(&lexer);
    printf("Ports string: %s", ports);
    return (SUCCESS);
}
