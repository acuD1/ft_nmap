/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:35 by cempassi          #+#    #+#             */
/*   Updated: 2021/08/02 07:50:19 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_freetab(char ***tab)
{
	char	**tmp;
	int		i;

	tmp = *tab;
	i = 0;
	if (*tab)
	{
		while (tmp[i])
			ft_strdel(&tmp[i++]);
		free(*tab);
	}
	*tab = NULL;
}
