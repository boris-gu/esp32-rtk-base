#pragma once

#include <stdint.h>
#include "ubx-default-msg.h"

typedef enum {
  UBX_NAV_PVT_FIXTYPE_NOFIX,
  UBX_NAV_PVT_FIXTYPE_DR,
  UBX_NAV_PVT_FIXTYPE_2D,
  UBX_NAV_PVT_FIXTYPE_3D,
  UBX_NAV_PVT_FIXTYPE_GNSS_DR,
  UBX_NAV_PVT_FIXTYPE_TIME
} ubx_nav_pvt_fixType_t;

typedef struct {
  uint32_t iTOW; // [ ms ] GPS time of week of the navigation epoch
  uint16_t year; // [ y ]     Year (UTC)
  uint8_t month; // [ month ] Month, range 1..12 (UTC)
  uint8_t day;   // [ d ]     Day of month, range 1..31 (UTC
  uint8_t hour;  // [ h ]     Hour of day, range 0..23 (UTC)
  uint8_t min;   // [ min ]   Minute of hour, range 0..59 (UTC)
  uint8_t sec;   // [ s ]     Seconds of minute, range 0..60 (UTC)

  uint8_t valid;   // [ - ] Validity flags
  uint32_t tAcc;   // [ ns ] Time accuracy estimate (UTC)
  int32_t nano;    // [ ns ] Fraction of second, range -1e9 .. 1e9 (UTC)
  uint8_t fixType; // [ - ] GNSSfix Type
  uint8_t flags;   // [ - ] Fix status flags
  uint8_t flags2;  // [ - ] Additional flags
  uint8_t numSV;   // [ - ] Number of satellites used in Nav Solution

  int32_t lon; // [ 1e-7 | deg ] Longitude
  int32_t lat; // [ 1e-7 | deg ] Latitude
  int32_t height;  // [ mm ] Height above ellipsoid
  int32_t hMSL;    // [ mm ] Height above mean sea level
  uint32_t hAcc;   // [ mm ] Horizontal accuracy estimate
  uint32_t vAcc;   // [ mm ] Vertical accuracy estimate
  int32_t velN;    // [ mm/s ] NED north velocity
  int32_t velE;    // [ mm/s ] NED east velocity
  int32_t velD;    // [ mm/s ] NED down velocity
  int32_t gSpeed;  // [ mm/s ] Ground Speed (2-D)
  int32_t headMot; // [ 1e-5 | deg ] Heading of motion (2-D)

  uint32_t sAcc;    // [ mm/s ]       Speed accuracy estimate
  uint32_t headAcc; // [ 1e-5 | deg ] Heading accuracy estimate (both motion and vehicle)
  uint16_t pDOP;    // [ 0.01 | - ]   Position DOP
  uint16_t flags3;  // [ - ] Additional flags
  // uint8_t reserved[4]
  int32_t headVeh; // [ 1e-5 | deg ] Heading of vehicle (2-D)
  int16_t magDec;  // [ 1e-5 | deg ] Magnetic declination
  uint16_t magAcc; // [ 1e-5 | deg ] Magnetic declination accuracy
} ubx_nav_pvt_t;

void ubx_default_msg_t2ubx_nav_pvt(ubx_default_msg_t* msg_in, ubx_nav_pvt_t* msg_out);

uint8_t get_ubx_nav_pvt_flags_diffSoln(ubx_nav_pvt_t* msg);

uint8_t get_ubx_nav_pvt_flags_carrSoln(ubx_nav_pvt_t* msg);