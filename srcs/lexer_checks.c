/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 17:04:00 by cempassi          #+#    #+#             */
/*   Updated: 2021/07/05 19:15:21 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_nmap.h"

bool is_source_finished(t_lexer *lexer)
{
    if (lexer->vector->buffer[0] == '\0' && lexer->source[0] == '\0')
        return (true);
    return (false);
}

bool is_set_state(t_lexer *lexer)
{
    if (lexer->state == L_SET_SINGLE)
        return (true);
    if (lexer->state == L_SET_START)
        return (true);
    if (lexer->state == L_SET_END)
        return (true);
    return (false);
}

bool is_exit_state(t_lexer *lexer)
{
    if (lexer->state == L_FINISH)
        return (true);
    if (lexer->state == L_ERROR)
        return (true);
    if (lexer->state == L_FAILURE)
        return (true);
    return (false);
}
