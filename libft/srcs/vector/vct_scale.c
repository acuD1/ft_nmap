/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:39 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:40:34 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int8_t	vct_scale(t_vector *vector)
{
	char *new;

	if ((new = ft_strnew(vector->size + vector->scale)) == NULL)
		return (-1);
	vector->size += vector->scale;
	ft_strncpy(new, vector->buffer, vct_len(vector));
	ft_strdel(&vector->buffer);
	vector->buffer = new;
	return (0);
}
