/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelfirst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:21 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:22 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int		ft_lstdelfirst(t_list **alst, void (*del)(void *))
{
	if (!alst || !*alst)
		return (-1);
	ft_lstdelone(alst, del);
	return (0);
}
