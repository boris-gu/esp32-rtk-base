#pragma once

#include <stdint.h>
#include "ubx-default-msg.h"

typedef struct {
  uint8_t version; // 0x00 for this version
  // uint8_t reserved0[3]
  uint32_t iTOW; // [ ms ] GPS time of week of the navigation epoch
  uint32_t dur;  // [ s ]  Passed survey-in observation time

  int32_t meanX; // [ cm ] Current survey-in mean position ECEF X coordinate
  int32_t meanY; // [ cm ] Current survey-in mean position ECEF Y coordinate
  int32_t meanZ; // [ cm ] Current survey-in mean position ECEF Z coordinate

  int8_t meanXHP; // [ 0.1_mm ] Current high-precision survey-in mean position ECEF X coordinate. Must be in the range -99..+99
  int8_t meanYHP; // [ 0.1_mm ] Current high-precision survey-in mean position ECEF Y coordinate. Must be in the range -99..+99
  int8_t meanZHP; // [ 0.1_mm ] Current high-precision survey-in mean position ECEF Z coordinate. Must be in the range -99..+99

  // uint8_t reserved1
  uint32_t meanAcc; // [ 0.1_mm ] Current survey-in mean position accuracy
  uint32_t obs;     // [ - ]      Number of position observations used during surveyin
  uint8_t valid;    // [ - ]      Survey-in position validity flag, 1 = valid, otherwise 0
  uint8_t active;   // [ - ]      Survey-in in progress flag, 1 = in-progress, otherwise 0
  // uint8_t reserved2[2]
} ubx_nav_svin_t;

void ubx_default_msg_t2ubx_nav_svin(ubx_default_msg_t* msg_in, ubx_nav_svin_t* msg_out);
