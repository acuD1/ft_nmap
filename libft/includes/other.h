/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:18 by cempassi          #+#    #+#             */
/*   Updated: 2021/07/26 12:45:11 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTHER_H
# define OTHER_H
# include <stdbool.h>

bool				ft_isalpha(int c);
bool				ft_isalnum(int c);
bool				ft_isascii(int c);
bool				ft_isdigit(int c);
bool				ft_isprint(int c);
int	    		    ft_tolower(int c);
int					ft_toupper(int c);
int                 ft_tablen(char **tab);

#endif
