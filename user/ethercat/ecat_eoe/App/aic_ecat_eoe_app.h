#ifndef AIC_ECAT_EOE_APP_H_
#define AIC_ECAT_EOE_APP_H_

#include <all_inc.h>
#include "ecateoe.h"

#define    ENET_FRAME_TYPE_IP               0x0008
#define    ENET_FRAME_TYPE_ARP              0x0608

#define    ENET_HEADER_LEN                  14
#define    IP_HEADER_MIN_LEN                20
#define    ARP_IP_HEADER_LEN                28
#define    IP_PROTOCOL_ICMP                 1


#define    ICMP_TYPE_ECHO_REPLY             0
#define    ICMP_TYPE_DEST_UNREACHABLE       3
#define    ICMP_TYPE_SOURCE_CLOSED          4
#define    ICMP_TYPE_REDIRECT               5
#define    ICMP_TYPE_ECHO                   8
#define    ICMP_TYPE_TIME_EXCEEDED          11
#define    ICMP_TYPE_PARA_PROBLEM           12
#define    ICMP_TYPE_TIMESTAMP              13
#define    ICMP_TYPE_TIMESTAMP_REPLY        14
#define    ICMP_TYPE_INFO_REQUEST           15
#define    ICMP_TYPE_INFO_REPLY             16

#define    ENET_ARP_HW_ADDR_SPACE_ETHERNET  0x0100
#define    ENET_ARP_OPCODE_REQUEST          0x0100
#define    ENET_ARP_OPCODE_REPLY            0x0200

typedef struct
{
    u8 data[6];
} ENET_ADDR;

typedef struct MBX_STRUCT_PACKED_START
{
    ENET_ADDR    destination;
    ENET_ADDR    source;
    u16          frame_type;
} MBX_STRUCT_PACKED_END
ENET_FRAME_HEADER;

typedef struct MBX_STRUCT_PACKED_START
{
    u8        ver_and_len;
    u8        tos;
    u16       len;
    u16       id;
    u16       fra;
    u8        ttl;
    u8        protocol;
    u16       cksum;
    u16       src[2];
    u16       dest[2];
} MBX_STRUCT_PACKED_END
ENET_IP_HEADER;

typedef struct MBX_STRUCT_PACKED_START
{
    u8       type;
    u8       code;
    u16      cksum;
    u16      id;
    u16      seqNo;
} MBX_STRUCT_PACKED_END
ENET_ICMP_HEADER;


typedef struct MBX_STRUCT_PACKED_START
{
    ENET_FRAME_HEADER       head;
    ENET_IP_HEADER          ip;
    union
    {
        ENET_ICMP_HEADER    icmp;
        u8                  data[(ETHERNET_MAX_FRAME_LEN)-(ENET_HEADER_LEN)-(IP_HEADER_MIN_LEN)];
    } ip_data;
} MBX_STRUCT_PACKED_END
ENET_IP_ICMP_FRAME;

typedef struct MBX_STRUCT_PACKED_START
{
    u16                  hw_type;
    u16                  protocol_type;
    u8                   hw_addr_len;
    u8                   protocol_addr_len;
    u16                  op;
    ETHERNET_ADDRESS     src_mac ;
    u16                  src_ip[2];
    ETHERNET_ADDRESS     dest_mac;
    u16                  dest_ip[2];
}MBX_STRUCT_PACKED_END
ENET_ARP_IP_HEADER;



#endif
