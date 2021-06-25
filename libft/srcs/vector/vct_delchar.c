/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_delchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:37 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int8_t	vct_del_char(t_vector *vector, uint64_t index)
{
	if (index > vct_len(vector))
		return (-1);
	shift_left(vector, index);
	return (0);
}
