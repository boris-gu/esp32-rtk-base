#include <string.h>
#include "ubx-cfg-rst.h"
#include "ubx-enum.h"
#include "ubx-default-msg.h"

int ubx_cfg_rst2array(ubx_cfg_rst_t* msg_in, uint8_t* msg_out) {
  msg_out[0] = UBX_SYNC1;
  msg_out[1] = UBX_SYNC2;
  msg_out[2] = (uint8_t)(UBX_CFG_RST & 0xFF);
  msg_out[3] = (uint8_t)(UBX_CFG_RST >> 8);
  uint16_t length = 4;
  memcpy(&msg_out[4], &length, sizeof(uint16_t));
  // PAYLOAD
  memcpy(&msg_out[6], &msg_in->navBbrMask, sizeof(uint16_t));
  memcpy(&msg_out[8], &msg_in->resetMode, sizeof(uint8_t));
  msg_out[9] = 0; // reserved
  return ubx_array_checksum(msg_out);
}
