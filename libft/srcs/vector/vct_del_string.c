/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_del_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:37 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Deletes a one or more character in the specified vector.
**	Starting from index start to start+len.
**	It also shifts the rest of the buffer accordingly.
**	Always returns 0.
*/

int8_t	vct_del_string(t_vector *vector,
					uint64_t start, uint64_t len)
{
	shift_nleft(vector, start, len);
	return (0);
}
