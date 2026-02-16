#include <string.h>
#include "ubx-cfg-valset.h"
#include "ubx-enum.h"
#include "ubx-default-msg.h"

int ubx_cfg_valset2array(ubx_cfg_valset_t* msg_in, uint8_t* msg_out) {
  // TODO: Сделать для нескольких возможных пар (не больше 64)
  msg_out[0] = UBX_SYNC1;
  msg_out[1] = UBX_SYNC2;
  msg_out[2] = (uint8_t)(UBX_CFG_VALSET & 0xFF); // memcpy не работает, т.к. UBX_CFG_VALSET - макрос
  msg_out[3] = (uint8_t)(UBX_CFG_VALSET >> 8);
  uint16_t length = 4 + (4 + msg_in->cfgData_value_size); // для одной пары ключ-значение
  memcpy(&msg_out[4], &length, sizeof(uint16_t));
  // PAYLOAD
  msg_out[6] = msg_in->version;
  msg_out[7] = msg_in->layers;
  msg_out[8] = 0; // reserved
  msg_out[9] = 0; // reserved
  // cfgData_key
  memcpy(&msg_out[10], &msg_in->cfgData_key, sizeof(uint32_t));
  // cfgData_value
  memcpy(&msg_out[14], &msg_in->cfgData_value, msg_in->cfgData_value_size);
  return ubx_array_checksum(msg_out);
}
