#include <string.h>
#include "ubx-nav-svin.h"

void ubx_default_msg_t2ubx_nav_svin(ubx_default_msg_t* msg_in, ubx_nav_svin_t* msg_out) {
  msg_out->version = msg_in->payload[0];

  memcpy(&msg_out->iTOW, &msg_in->payload[4], 4);
  memcpy(&msg_out->dur, &msg_in->payload[8], 4);
  memcpy(&msg_out->meanX, &msg_in->payload[12], 4);
  memcpy(&msg_out->meanY, &msg_in->payload[16], 4);
  memcpy(&msg_out->meanZ, &msg_in->payload[20], 4);

  msg_out->meanXHP = msg_in->payload[24];
  msg_out->meanYHP = msg_in->payload[25];
  msg_out->meanZHP = msg_in->payload[26];

  memcpy(&msg_out->meanAcc, &msg_in->payload[28], 4);
  memcpy(&msg_out->obs, &msg_in->payload[32], 4);

  msg_out->valid = msg_in->payload[36];
  msg_out->active = msg_in->payload[37];
}

