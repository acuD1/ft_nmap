/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:32 by cempassi          #+#    #+#             */
/*   Updated: 2022/01/12 18:05:55 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <unistd.h>

ssize_t ft_strcspn(const char *s, const char *charset)
{
    ssize_t      i;
    const char *c;

    i = 0;
    if (!s || !charset)
        return (-1);
    while (*s)
    {
        c = charset;
        while (*c)
        {
            if (*s == *c)
                return (i);
            c++;
        }
        s++;
        i++;
    }
    return (i);
}
