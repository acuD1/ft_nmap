/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_cut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:36 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:36 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Deletes the first character of the specified vector,
**	And shifts the rest of the buffer one character to the left.
**	Always returns 0
*/

int8_t	vct_cut(t_vector *vector)
{
	shift_left(vector, 0);
	return (0);
}
