/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:39 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/25 21:31:40 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*vct_sub(t_vector *vector, uint64_t start, uint64_t len)
{
	return (ft_strsub(vector->buffer, (unsigned int)start, (size_t)len));
}
