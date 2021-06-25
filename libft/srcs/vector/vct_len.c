/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:37 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:39:32 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Return then length of the vector
** Equivalent to strlen(vector->buffer)
*/

uint64_t			vct_len(t_vector *vector)
{
	return (ft_strlen(vct_get_string(vector)));
}
