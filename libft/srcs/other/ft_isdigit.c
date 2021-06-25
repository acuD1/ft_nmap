/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:27 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 17:23:44 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"

int		ft_isdigit(int c)
{
	return (c >= '0' && c <= '9' ? 1 : 0);
}
