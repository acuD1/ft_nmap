/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_ncpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:38 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:38 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Copies `len` character from the `source` vector to the `dest` vector.
**	Resizes accordingly.
*/

int8_t	vct_ncpy(t_vector *dest, t_vector *source,
						uint64_t len)
{
	vct_scpy(dest, source->buffer, len);
	return (0);
}
