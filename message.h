#ifndef __MESSAGE_H_
#define __MESSAGE_H_
#include <stdint.h>

#define MCAST_ADDR "239.255.43.21"
#define MCAST_PORT 5555

#define MCAST_MSG_MAGIC 0xABCD
struct Message {
    uint16_t magic;
    uint8_t type;
    uint8_t reserved;
    uint8_t from[6];
    uint8_t to[6];
    uint16_t size;
    uint8_t data[1400];
};

#define MCAST_MSG_PROBE              0x01
#define MCAST_MSG_PROBE_RESPONSE     0x02
#define MCAST_MSG_GETPUBKEY          0x03
#define MCAST_MSG_GETPUBKEY_RESPONSE 0x04
#define MCAST_MSG_SETAESKEY          0x05
#define MCAST_MSG_SETAESKEY_ACK      0x06
#define MCAST_MSG_CIPHERDATA         0x07
//#define MCAST_MSG_CIPHERDATA_ACK     0x08

#endif
