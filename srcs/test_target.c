/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_target.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:09:34 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/15 17:40:28 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

uint8_t     test_target(t_target *target)
{
    int     sockfd      = 0;
    ssize_t bytes_sent  = 0;

    if ((sockfd = socket(((struct sockaddr_in *)&target->dst)->sin_family,
                         SOCK_RAW, IPPROTO_UDP)) == -1)
    {
        dprintf(STDERR_FILENO, "\nft_nmap: socket(): %s\n", strerror(errno));
        return (FAILURE);
    }

    if ((bytes_sent = sendto(sockfd, "", 1, 0,
                            (struct sockaddr *)&target->dst,
                            sizeof(target->dst))) == -1)
    {
        dprintf(STDERR_FILENO, "\nft_nmap: sendto(): %s\n", strerror(errno));
        return (FAILURE);
    }

    close(sockfd);

    return (SUCCESS);
}
