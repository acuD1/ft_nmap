/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:56:25 by arsciand          #+#    #+#             */
/*   Updated: 2021/06/25 17:40:54 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_tabdel(char ***array)
{
    char    **tmp = *array;

    if (!tmp)
        return ;
    for (size_t i = 0; tmp[i]; i++)
        ft_strdel(&(tmp[i]));
    free(*array);
    *array = NULL;
}
