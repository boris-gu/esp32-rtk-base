#include <string.h>
#include "ubx-default-msg.h"
#include "ubx-enum.h"

uint8_t ubx_check;

void ubx_checksum(ubx_default_msg_t* msg) {
  // msg_class
  msg->ck_a = (uint8_t)(msg->header & 0xFF);
  msg->ck_b = msg->ck_a;
  // msg_id
  msg->ck_a += (uint8_t)(msg->header >> 8);
  msg->ck_b += msg->ck_a;
  // length
  msg->ck_a += (uint8_t)(msg->length & 0xFF);
  msg->ck_b += msg->ck_a;
  msg->ck_a += (uint8_t)(msg->length >> 8);
  msg->ck_b += msg->ck_a;
  // payload
  for(int16_t i = 0; i < msg->length; i++) {
    msg->ck_a += msg->payload[i];
    msg->ck_b += msg->ck_a;
  }
}

uint8_t ubx_parse_char(uint8_t rx_byte, ubx_default_msg_t* rx_msg, ubx_read_track_t* track) {
  switch (track->status) {
    case UBX_READ_SYNC1: {
      if (rx_byte == UBX_SYNC1) {
        track->status = UBX_READ_SYNC2;
      }
      break;
    }
    case UBX_READ_SYNC2: {
      if (rx_byte == UBX_SYNC2) {
        track->byte_of_field = 0;
        track->status = UBX_READ_HEADER;
      } else {
        track->status = UBX_READ_SYNC1;
        ubx_parse_char(rx_byte, rx_msg, track);
      }
      break;
    }
    case UBX_READ_HEADER: {
      if (track->byte_of_field == 0) { // Читаем первый байт uint16_t
        rx_msg->header = rx_byte;
        track->byte_of_field += 1;
      } else { // Второй байт
        rx_msg->header += (uint16_t)rx_byte << 8;
        if (rx_msg->header == UBX_NAV_PVT ||
            rx_msg->header == UBX_NAV_SVIN ||
            rx_msg->header == UBX_ACK_ACK ||
            rx_msg->header == UBX_ACK_NAK ||
            rx_msg->header == UBX_CFG_VALSET ||
            rx_msg->header == UBX_CFG_VALGET ||
            rx_msg->header == UBX_CFG_VALDEL) {
          track->byte_of_field = 0;
          track->status = UBX_READ_LENGTH;
        } else {
          track->status = UBX_READ_SYNC1;
          ubx_parse_char(rx_byte, rx_msg, track);
        }
      }
      break;
    }
    case UBX_READ_LENGTH: {
      if (track->byte_of_field == 0) {
        rx_msg->length = rx_byte;
        track->byte_of_field += 1;
      } else {
        rx_msg->length += (uint16_t)rx_byte << 8;
        track->byte_of_field = 0;
        track->status = UBX_READ_PAYLOAD;
      }
      // Длина может быть любой, поэтому тут нет проверки и возврата на UBX_READ_SYNC1
      break;
    }
    case UBX_READ_PAYLOAD: {
      if (track->byte_of_field < rx_msg->length) {
        rx_msg->payload[track->byte_of_field] = rx_byte;
        track->byte_of_field += 1;
      } else {
        ubx_checksum(rx_msg);
        track->byte_of_field = 0xDA;
        track->status = UBX_READ_CK_A;
        ubx_parse_char(rx_byte, rx_msg, track);
      }
      break;
    }
    case UBX_READ_CK_A: {
      if (rx_byte == rx_msg->ck_a) {
        track->status = UBX_READ_CK_B;
      } else {
        track->status = UBX_READ_SYNC1;
        ubx_parse_char(rx_byte, rx_msg, track);
      }
      break;
    }
    case UBX_READ_CK_B: {
      track->status = UBX_READ_SYNC1;
      if (rx_byte == rx_msg->ck_b) {
        return 1;
      }
      break;
    }
    default: {
      track->status = UBX_READ_SYNC1;
    }
  }
  return 0;
}
