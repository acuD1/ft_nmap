/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_self.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:08:10 by cempassi          #+#    #+#             */
/*   Updated: 2022/01/02 17:50:08 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void eraser(t_list **head, t_list *prev, t_list *current, t_cmp cmp)
{
    if (!current)
        return ;
    else if (cmp(current->data, *head))
    {
        prev->next = current->next;
        ft_lstdelone(&current, NULL);
        ft_lst_remove_self(head, cmp);
    }
    else
        eraser(head, current, current->next, cmp);
}

void ft_lst_remove_self(t_list **lst, t_cmp cmp)
{
    t_list *tmp;

    tmp = *lst;
    if (cmp((*lst)->data, *lst))
    {
        tmp = (*lst)->next;
        ft_lstdelone(&(*lst), NULL);
        *lst = tmp;
        ft_lst_remove_self(lst, cmp);
    }
    else
        eraser(lst, *lst, (*lst)->next, cmp);
}
