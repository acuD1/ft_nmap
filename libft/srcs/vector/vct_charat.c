/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_charat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:36 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:36 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Returns the character at the index `index` of the specified vector.
**	Or 0 if index is bigger than the buffer length.
*/

char	vct_charat(t_vector *vct, uint64_t index)
{
	return (vct->buffer[index]);
}
