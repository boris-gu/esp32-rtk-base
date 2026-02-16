#pragma once

#include <stdint.h>

#define UBX_MAX_PAYLOAD_LEN 256 // FIXME: Может быть огромной длины

typedef enum {
  UBX_READ_SYNC1,
  UBX_READ_SYNC2,
  UBX_READ_HEADER,
  UBX_READ_LENGTH,
  UBX_READ_PAYLOAD,
  UBX_READ_CK_A,
  UBX_READ_CK_B
} ubx_read_status_t;

typedef struct {
  ubx_read_status_t status;
  uint16_t byte_of_field;
} ubx_read_track_t;

typedef struct {
  // uint8_t sync1;
  // uint8_t sync2;
  uint16_t header; // msg_class + msg_id
  uint16_t length;
  uint8_t payload[UBX_MAX_PAYLOAD_LEN];
  uint8_t ck_a;
  uint8_t ck_b;
} ubx_default_msg_t;

void ubx_checksum(ubx_default_msg_t* msg);

uint16_t ubx_array_checksum(uint8_t* msg);

uint8_t ubx_parse_char(uint8_t rx_byte, ubx_default_msg_t* rx_msg, ubx_read_track_t* track);
