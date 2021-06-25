/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:39 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:39 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*vct_sub(t_vector *vector, uint64_t start, uint64_t len)
{
	return (ft_strsub(vector->buffer, start, len));
}
