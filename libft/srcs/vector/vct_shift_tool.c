/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_shift_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:39 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/25 21:30:53 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		shift_nright(t_vector *vector, uint64_t start, uint64_t offset)
{
	uint64_t	vlen;

	vlen = vct_len(vector);
	while (vlen >= start)
	{
		vector->buffer[vlen + offset] = vector->buffer[vlen];
		--vlen;
	}
}

void		shift_nleft(t_vector *vector, uint64_t start, uint64_t offset)
{
	uint64_t	vlen;
	int64_t			nb;

	vlen = vct_len(vector);
	nb = (int64_t)(vlen - offset);
	while (nb < 0 && offset >= 1)
		offset--;
	vlen -= offset;
	while (start <= vlen)
	{
		vector->buffer[start] = vector->buffer[start + offset];
		++start;
	}
}

void		shift_right(t_vector *vector, uint64_t start)
{
	shift_nright(vector, start, 1);
}

void		shift_left(t_vector *vector, uint64_t start)
{
	shift_nleft(vector, start, 1);
}
