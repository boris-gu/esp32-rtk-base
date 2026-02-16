#include <string.h>
#include "ubx-cfg-valdel.h"
#include "ubx-enum.h"
#include "ubx-default-msg.h"

int ubx_cfg_valdel2array(ubx_cfg_valdel_t* msg_in, uint8_t* msg_out) {
  // TODO: Сделать для нескольких ключей (не больше 64)
  msg_out[0] = UBX_SYNC1;
  msg_out[1] = UBX_SYNC2;
  msg_out[2] = (uint8_t)(UBX_CFG_VALDEL & 0xFF);
  msg_out[3] = (uint8_t)(UBX_CFG_VALDEL >> 8);
  uint16_t length = 8; // для одного ключа
  memcpy(&msg_out[4], &length, sizeof(uint16_t));
  // PAYLOAD
  msg_out[6] = msg_in->version;
  msg_out[7] = msg_in->layers;
  msg_out[8] = 0; // reserved
  msg_out[9] = 0; // reserved
  // KEYS
  memcpy(&msg_out[10], &msg_in->key, sizeof(uint32_t));
  return ubx_array_checksum(msg_out);
}
