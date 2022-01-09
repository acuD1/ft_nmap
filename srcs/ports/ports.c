/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ports.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:21:28 by cempassi          #+#    #+#             */
/*   Updated: 2022/01/09 18:07:30 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include "list.h"
#include "memory.h"
#include <limits.h>
#include <stdio.h>

static uint8_t init_lexer(t_lexer *lexer, char *ports)
{
    ft_bzero(lexer, sizeof(t_lexer));
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
    if (check > USHRT_MAX || ft_strlen(lexer->vector->buffer) > 5)
    {
        lexer->state = L_ERROR;
        dprintf(STDERR_FILENO, "ft_nmap: port number too big, maximum is %i\n",
                USHRT_MAX);
    }
    else
    {
        *port = (uint16_t)check;
        ft_strclr(lexer->vector->buffer);
        if (lexer->state == L_SET_SINGLE || lexer->state == L_SET_END)
            lexer->state = L_TOKENIZE;
        else if (lexer->state == L_SET_START)
            lexer->state = L_SET_RANGE;
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

static void process_range(t_lexer *lexer)
{
    if (ft_isdigit(lexer->source[0]) == true)
    {
        vct_add(lexer->vector, lexer->source[0]);
        ++lexer->source;
    }
    else if (lexer->source[0] == '\0')
    {
        lexer->state = L_SET_END;
    }
    else if (lexer->source[0] == ',')
    {
        lexer->state = L_SET_END;
        ++lexer->source;
    }
    else
    {
        lexer->state = L_ERROR;
    }
}

static void process_lexer(t_lexer *lexer)
{
    if (lexer->state == L_TOKENIZE)
        tokenizer(lexer);
    else if (is_source_finished(lexer))
        lexer->state = L_OUT;
    else if (lexer->state == L_BASE)
        process_base(lexer);
    else if (lexer->state == L_SET_RANGE)
        process_range(lexer);
    else if (is_set_state(lexer))
        set_port(lexer);
}

static void out_lexer(t_lexer *lexer)
{
    vct_del(&lexer->vector);
    lexer->state = L_FINISH;
}

static int find_port(void *data, void *to_find)
{
    t_port *port = to_find;
    t_port *current = data;
    if (data == to_find)
        return (0);
    else if (port->type == E_PORT_SINGLE && current->type == E_PORT_SINGLE)
    {
        if (port->data.port == current->data.port)
            return (1);
    }
    else if (port->type == E_PORT_SINGLE && current->type == E_PORT_RANGE)
    {
        uint16_t port_nbr = port->data.port;
        uint16_t range_start = current->data.range[RANGE_START];
        uint16_t range_end = current->data.range[RANGE_END];
        if (port_nbr >= range_start && port_nbr <= range_end)
            return (1);
    }
    else if (port->type == E_PORT_RANGE && current->type == E_PORT_RANGE)
    {
        uint16_t port_start = port->data.range[RANGE_START];
        uint16_t port_end = port->data.range[RANGE_END];
        uint16_t current_start = current->data.range[RANGE_START];
        uint16_t current_end = current->data.range[RANGE_END];

        if (port_start >= current_start && port_end <= current_end)
            return (1);
        if (port_start < current_start && port_end >= current_start && port_end <= current_end)
        {
            current->data.range[RANGE_START] = port_start;
            return (1);
        }
        if (port_end > current_end && port_start >= current_start && port_start <= current_end)
        {
            current->data.range[RANGE_END] = port_end;
            return (1);
        }
        if (port_start <= current_start && port_end >= current_end)
        {
            current->data.range[RANGE_START] = port_start;
            current->data.range[RANGE_END] = port_end;
            return (1);
        }
    }
    return (0);
}

static int check_port(void *data, void *lst)
{
    return (ft_lstfind(lst, data, find_port) ? 1 : 0);
}

uint8_t parse_ports(t_target *target, char *ports)
{
    t_lexer lexer;

    if (init_lexer(&lexer, ports) == FAILURE)
        return (FAILURE);
    while (is_exit_state(&lexer) == false)
        lexer.state == L_OUT ? out_lexer(&lexer) : process_lexer(&lexer);
    vct_del(&lexer.vector);
    if (lexer.state != L_FINISH)
    {
        ft_lstdel(&lexer.result, NULL);
        return (FAILURE);
    }
    ft_lst_remove_self(&lexer.result, check_port);
    target->ports = lexer.result;
    return (SUCCESS);
}
