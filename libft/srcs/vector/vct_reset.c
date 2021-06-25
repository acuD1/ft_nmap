/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_reset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:38 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:40:02 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Resets the specified vector, to the default size and scale.
**	This erases the holded content.
**	Returns 0 on success or -1 on allocation error.
*/

int8_t		vct_reset(t_vector *vector)
{
	char *new;

	if (vector == NULL)
		return (0);
	if (!(new = ft_strnew(DEFAULT_VECTOR_SIZE)))
		return (-1);
	ft_strdel(&(vector->buffer));
	vector->buffer = new;
	vector->size = DEFAULT_VECTOR_SIZE;
	vector->scale = DEFAULT_VECTOR_SCALE;
	return (0);
}
