/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_insert_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:37 by cempassi          #+#    #+#             */
/*   Updated: 2021/12/31 17:46:29 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

/*
**	Inserts the string `str` into the specified vector,
**	starting at the index `index`.
**	Shifting the following characters and reallocates if neccesary.
**	Returns 0 on success or -1 if index is bigger than the vector length.
*/

int8_t	vct_insert_string(t_vector *vector,
					char *str, uint64_t index)
{
    (void)index;
    for (size_t i = 0 ; str[i]; i++)
    {
        if (vct_add(vector, str[i]) != SUCCESS)
            return (-1);
    }
	return (0);
}
