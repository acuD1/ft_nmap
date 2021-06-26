/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:57:44 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/26 17:06:08 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void handle_vector_empty(t_lexer *lexer)
{
    if (lexer->source[0] == '[')
        lexer->state = L_LBRACE;
    else if (lexer->source[0] == '(')
        lexer->state = L_PARENT;
    else if (lexer->source[0] == '~')
        lexer->state = L_EXCLUDE;
    else
        lexer->state = L_ERROR;
}

void handle_vector_data(t_lexer *lexer)
{
    if (lexer->source[0] == '\0' || lexer->source[0] == ',')
    {
        lexer->tmp_port.type = E_PORT_SINGLE;
        lexer->state = L_SET_SINGLE;
    }
    else if (lexer->source[0] == '-')
    {
        lexer->tmp_port.type = E_PORT_RANGE;
        lexer->state = L_SET_START;
    }
    else
        lexer->state = L_ERROR;
}

void process_base(t_lexer *lexer)
{
    if(ft_isdigit(lexer->source[0]))
        vct_add(lexer->vector, lexer->source[0]);
    else if (lexer->vector->buffer[0] == '\0')
        handle_vector_empty(lexer);
    else
        handle_vector_data(lexer);
    if (lexer->source[0])
        ++lexer->source;
}
