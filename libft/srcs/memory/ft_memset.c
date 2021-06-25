/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:26 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:37:53 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	if (!len)
		return (b);
	*((unsigned char *)b) = (unsigned char)c;
	while (--len > 0)
		((unsigned char *)b)[len] = (unsigned char)c;
	return (b);
}
