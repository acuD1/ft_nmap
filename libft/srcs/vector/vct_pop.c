/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_pop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:38 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:38 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Deletes the last character of the specified vector.
*/

int8_t	vct_pop(t_vector *vector)
{
	if (vct_len(vector) == 0)
		return (0);
	vector->buffer[vct_len(vector) - 1] = '\0';
	return (0);
}
