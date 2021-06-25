/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:32 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/24 17:06:50 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str.h"

void	ft_strdel(char **as)
{
	if (!as || *as == NULL)
		return ;
	free(*as);
	*as = NULL;
	return ;
}
