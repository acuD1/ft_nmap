/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getargslst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:21 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:21 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_getargslst(int ac, char **av)
{
	t_list	*lst;
	int		i;

	i = 1;
	lst = NULL;
	while (i < ac && av[i][0] == '-' && av[i][1] && av[i][1] != '-')
		i++;
	if (i < ac && av[i][0] == '-' && av[i][1] == '-' && !av[i][2])
		i++;
	if (i < ac)
	{
		while (i < ac)
		{
			ft_lstadd(&lst, ft_lstnew(av[i], ft_strlen(av[i]) + 1));
			i++;
		}
	}
	return (lst);
}
