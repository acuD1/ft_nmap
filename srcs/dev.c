/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 10:04:33 by arsciand          #+#    #+#             */
/*   Updated: 2021/08/13 10:06:42 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

/*
**  void DEV_FUNCTION(void)
**  {
**      dprintf(STDERFILENO, "This is a dev function\n");
**  }
*/

void                    *DEV_exec_thread(void *data)
{
    t_thread_data *thread_data = (t_thread_data *)data;

    dprintf(STDERR_FILENO, "[DEBUG] Thread -%hu- working ...\n", thread_data->thread_id);
    pthread_exit(NULL);
}
