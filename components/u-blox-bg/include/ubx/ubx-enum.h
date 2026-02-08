#pragma once

#define UBX_SYNC1 0xB5
#define UBX_SYNC2 0x62

typedef enum {
  UBX_NAV_PVT = 0x0701, // сначала msg_id потому что little-endian
  UBX_NAV_SVIN = 0x3b01,

  UBX_ACK_ACK = 0x0105,
  UBX_ACK_NAK = 0x0005,

  UBX_CFG_VALSET = 0x8a06,
  UBX_CFG_VALGET = 0x8b06,
  UBX_CFG_VALDEL = 0x8c06
} ubx_header_t;

