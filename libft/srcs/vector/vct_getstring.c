/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_getstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:37 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the pointer to the actual internal buffer of the specified vector.
*/

char	*vct_get_string(t_vector *vector)
{
	return (vector->buffer);
}
