/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   services_udp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:07:33 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/09 15:34:49 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

const char  *services_udp(uint16_t port)
{
    switch (port)
    {
        case 98:
            return "tacnews";
        case 106:
            return "3com-tsmux";
        case 113:
            return "auth";
        case 164:
            return "smip-agent";
        case 190:
            return "cacp";
        case 257:
            return "set";
        case 258:
            return "yak-chat";
        case 259:
            return "firewall1-rdp";
        case 264:
            return "fw1-or-bgmp";
        case 265:
            return "x-bone-ctl";
        case 474:
            return "tn-tl-w2";
        case 480:
            return "iafdbase";
        case 481:
            return "ph";
        case 482:
            return "xlog";
        case 486:
            return "avian";
        case 512:
            return "biff";
        case 513:
            return "who";
        case 514:
            return "syslog";
        case 520:
            return "route";
        case 545:
            return "appleqtcsrvr";
        case 603:
            return "idxp";
        case 623:
            return "asf-rmcp";
        case 625:
            return "dec_dlm";
        case 626:
            return "serialnumberd";
        case 635:
            return "mount";
        case 636:
            return "ldaps";
        case 640:
            return "pcnfs";
        case 650:
            return "bwnfs";
        case 691:
            return "msexch-routing";
        case 737:
            return "sometimes-rpc2";
        case 754:
            return "tell";
        case 760:
            return "ns";
        case 761:
            return "rxe";
        case 773:
            return "notify";
        case 774:
            return "acmaint_dbd";
        case 775:
            return "acmaint_transd";
        case 810:
            return "fcp-udp";
        case 901:
            return "smpnameres";
        case 902:
            return "ideafarm-door";
        case 903:
            return "ideafarm-panic";
        case 996:
            return "vsinet";
        case 998:
            return "puparp";
        case 999:
            return "applix";
        case 1000:
            return "ock";
        case 1012:
            return "sometimes-rpc1";
        default:
            return "unasigned";
    }
}
