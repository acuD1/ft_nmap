/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:36 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:36 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Deletes a vector and its internal buffer
*/

void		vct_del(t_vector **vector)
{
	if (vector == NULL || *vector == NULL)
		return ;
	ft_strdel(&(*vector)->buffer);
	free(*vector);
	*vector = NULL;
}
