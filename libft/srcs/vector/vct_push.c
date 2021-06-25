/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:38 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:38 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Adds the character `c` to the beginning of the vector(at the index 0).
**	Return 0 on success or -1 on allocation error.
**
**	As with all vector functions, if the LENGTH of the new buffer is bigger
**	than the buffers SIZE, an equivalent reallocation occurs.
*/

int8_t	vct_push(t_vector *vector, char c)
{
	if (vct_len(vector) + 1 >= vector->size)
		if (vct_scale(vector) == -1)
			return (-1);
	shift_right(vector, 0);
	vector->buffer[0] = c;
	return (0);
}
