/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendswith.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:32 by cempassi          #+#    #+#             */
/*   Updated: 2020/07/23 03:12:32 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strendswith(char *string, char *suffix)
{
	char	*ptr;
	size_t	diff;
	size_t	suffix_len;
	size_t	string_len;

	if (!string || !suffix)
		return (-1);
	ptr = string;
	suffix_len = ft_strlen(suffix);
	string_len = ft_strlen(string);
	diff = string_len - suffix_len;
	ptr += diff;
	return (ft_strnequ(ptr, suffix, suffix_len));
}
