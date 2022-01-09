/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   udp_payload.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 06:39:50 by arsciand          #+#    #+#             */
/*   Updated: 2022/01/08 06:40:03 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void    udp_payload(t_udp_payload *udp_payload, uint16_t port)
{
    switch (port)
    {
        case 7:
            udp_payload->payload        = UDP_ECHO_SERVICE;
            udp_payload->payload_len    = sizeof(UDP_ECHO_SERVICE) - 1;
            break;

        case 53:
            udp_payload->payload        = UDP_DNS_STATUS_REQUEST;
            udp_payload->payload_len    = sizeof(UDP_DNS_STATUS_REQUEST) - 1;
            break;

        case 111:
            udp_payload->payload        = UDP_RPC_CHECK;
            udp_payload->payload_len    = sizeof(UDP_RPC_CHECK) - 1;
            break;

        case 123:
            udp_payload->payload        = UDP_NTP_REQUEST;
            udp_payload->payload_len    = sizeof(UDP_NTP_REQUEST) - 1;
            break;

        case 137:
            udp_payload->payload        = UDP_NBT_STAT;
            udp_payload->payload_len    = sizeof(UDP_NBT_STAT) - 1;
            break;


        case 161:
            udp_payload->payload        = UDP_SNMP_V3_GET_REQUEST;
            udp_payload->payload_len    = sizeof(UDP_SNMP_V3_GET_REQUEST) - 1;
            break;

        case 177:
            udp_payload->payload        = UDP_XMDCP;
            udp_payload->payload_len    = sizeof(UDP_XMDCP) - 1;
            break;

        case 389:
            udp_payload->payload        = UDP_LDAP;
            udp_payload->payload_len    = sizeof(UDP_LDAP) - 1;
            break;

        case 427:
            udp_payload->payload        = UDP_SVRLOC;
            udp_payload->payload_len    = sizeof(UDP_SVRLOC) - 1;
            break;

        case 443:
        case 853:
        case 4433:
        case 4740:
        case 5349:
        case 5684:
        case 5868:
        case 6514:
        case 6636:
        case 8232:
        case 10161:
        case 10162:
        case 12346:
        case 12446:
        case 12546:
        case 12646:
        case 12746:
        case 12846:
        case 12946:
        case 13046:
            udp_payload->payload        = UDP_DTLS;
            udp_payload->payload_len    = sizeof(UDP_DTLS) - 1;
            break;

        case 500:
            udp_payload->payload        = UDP_ISAKMP;
            udp_payload->payload_len    = sizeof(UDP_ISAKMP) - 1;
            break;

        case 520:
            udp_payload->payload        = UDP_RIPV1;
            udp_payload->payload_len    = sizeof(UDP_RIPV1) - 1;
            break;

        case 623:
            udp_payload->payload        = UDP_IPMB;
            udp_payload->payload_len    = sizeof(UDP_IPMB) - 1;
            break;

        case 1194:
            udp_payload->payload        = UDP_OPENVPN;
            udp_payload->payload_len    = sizeof(UDP_OPENVPN) - 1;
            break;

        case 1645:
        case 1812:
            udp_payload->payload        = UDP_ACCESS_REQUEST;
            udp_payload->payload_len    = sizeof(UDP_ACCESS_REQUEST) - 1;
            break;

        case 2049:
            udp_payload->payload        = UDP_NFS;
            udp_payload->payload_len    = sizeof(UDP_NFS) - 1;
            break;

        case 5351:
            udp_payload->payload        = UDP_NAT_PMP;
            udp_payload->payload_len    = sizeof(UDP_NAT_PMP) - 1;
            break;

        case 5353:
            udp_payload->payload        = UDP_DNS_SD;
            udp_payload->payload_len    = sizeof(UDP_DNS_SD) - 1;
            break;

        case 5683:
            udp_payload->payload        = UDP_COAP;
            udp_payload->payload_len    = sizeof(UDP_COAP) - 1;
            break;

        case 27910:
            udp_payload->payload        = UDP_QUAKE2;
            udp_payload->payload_len    = sizeof(UDP_QUAKE2) - 1;
            break;

        case 2600:
        case 27960:
        case 44400:
            udp_payload->payload        = UDP_QUAKE3;
            udp_payload->payload_len    = sizeof(UDP_QUAKE3) - 1;
            break;

        case 3784:
            udp_payload->payload        = UDP_BFD_CONTROL;
            udp_payload->payload_len    = sizeof(UDP_BFD_CONTROL) - 1;
            break;

        case 8767:
            udp_payload->payload        = UDP_TS2;
            udp_payload->payload_len    = sizeof(UDP_TS2) - 1;
            break;

        case 11211:
            udp_payload->payload        = UDP_MEMCACHED;
            udp_payload->payload_len    = sizeof(UDP_MEMCACHED) - 1;
            break;

        default:
            break;
    }
}
