/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_scpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:39 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:39 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Copies `len` characters from the `source` string to the `dest` vector.
*/

int8_t	vct_scpy(t_vector *dest, char *source,
			uint64_t len)
{
	if (dest->size < len)
		vct_resize(dest, len + 1);
	ft_strncpy(dest->buffer, source, len);
	return (0);
}
