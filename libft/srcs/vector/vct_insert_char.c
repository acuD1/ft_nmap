/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_insert_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:37 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft.h"

/*
** Inserts the single character `c`  into the specified vector,
** at the index `index`.
** Return 0 on succes or -1 if the index
** is bigger than the length of the vector.
*/

int8_t	vct_insert_char(t_vector *vector, char c, uint64_t index)
{
	uint64_t	v_len;

	v_len = vct_len(vector);
	if (index > v_len)
		return (-1);
	if (v_len + 1 >= vector->size)
		vct_scale(vector);
	shift_right(vector, index);
	vector->buffer[index] = c;
	return (0);
}
