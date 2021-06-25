/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:23 by cempassi          #+#    #+#             */
/*   Updated: 2021/06/20 20:45:23 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmerge(t_list **alst, t_list *blst)
{
	if (*alst == NULL)
	{
		*alst = blst;
		return (*alst);
	}
	ft_lstaddback(alst, blst);
	return (*alst);
}
