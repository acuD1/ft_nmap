/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_scat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:39 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:39 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Concatenates `len` characters from the string `source`,
**	to the vector `dest`. Resizes automaticaly.
*/

int8_t	vct_scat(t_vector *dest, char *source,
						uint64_t len)
{
	if (dest->size < (vct_len(dest) + len))
		vct_resize(dest, (vct_len(dest) + len) + 1);
	ft_strncat(dest->buffer, source, len);
	return (0);
}
