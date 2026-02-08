#include <string.h>
#include "ubx-nav-pvt.h"

void ubx_default_msg_t2ubx_nav_pvt(ubx_default_msg_t* msg_in, ubx_nav_pvt_t* msg_out) {
  memcpy(&msg_out->iTOW, &msg_in->payload[0], 4);
  memcpy(&msg_out->year, &msg_in->payload[4], 2);
  msg_out->month = msg_in->payload[6];
  msg_out->day = msg_in->payload[7];
  msg_out->hour = msg_in->payload[8];
  msg_out->min = msg_in->payload[9];
  msg_out->sec = msg_in->payload[10];

  msg_out->valid = msg_in->payload[11];
  memcpy(&msg_out->tAcc, &msg_in->payload[12], 4);
  memcpy(&msg_out->nano, &msg_in->payload[16], 4);
  msg_out->fixType = msg_in->payload[20];
  msg_out->flags = msg_in->payload[21];
  msg_out->flags2 = msg_in->payload[22];
  msg_out->numSV = msg_in->payload[23];
  
  memcpy(&msg_out->lon, &msg_in->payload[24], 4);
  memcpy(&msg_out->lat, &msg_in->payload[28], 4);
  memcpy(&msg_out->height, &msg_in->payload[32], 4);
  memcpy(&msg_out->hMSL, &msg_in->payload[36], 4);
  memcpy(&msg_out->hAcc, &msg_in->payload[40], 4);
  memcpy(&msg_out->vAcc, &msg_in->payload[44], 4);
  memcpy(&msg_out->velN, &msg_in->payload[48], 4);
  memcpy(&msg_out->velE, &msg_in->payload[52], 4);
  memcpy(&msg_out->velD, &msg_in->payload[56], 4);
  memcpy(&msg_out->gSpeed, &msg_in->payload[60], 4);
  memcpy(&msg_out->headMot, &msg_in->payload[64], 4);

  memcpy(&msg_out->sAcc, &msg_in->payload[68], 4);
  memcpy(&msg_out->headAcc, &msg_in->payload[72], 4);
  memcpy(&msg_out->pDOP, &msg_in->payload[76], 2);
  memcpy(&msg_out->flags3, &msg_in->payload[78], 2);

  memcpy(&msg_out->headVeh, &msg_in->payload[84], 4);
  memcpy(&msg_out->magDec, &msg_in->payload[88], 2);
  memcpy(&msg_out->magAcc, &msg_in->payload[90], 2);
}

uint8_t get_ubx_nav_pvt_flags_diffSoln(ubx_nav_pvt_t* msg) {
  return (msg->flags >> 1) & 0b1;
}

uint8_t get_ubx_nav_pvt_flags_carrSoln(ubx_nav_pvt_t* msg) {
  return (msg->flags >> 6) & 0b11;
}
