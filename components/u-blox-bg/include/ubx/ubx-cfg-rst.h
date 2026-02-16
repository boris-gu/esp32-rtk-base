#pragma once

#include <stdint.h>

typedef enum {
  UBX_CFG_RST_NAVBBRMASK_eph =    0b0000000000000001, // Ephemeris
  UBX_CFG_RST_NAVBBRMASK_alm =    0b0000000000000010, // Almanac
  UBX_CFG_RST_NAVBBRMASK_health = 0b0000000000000100, // Health
  UBX_CFG_RST_NAVBBRMASK_klob =   0b0000000000001000, // Klobuchar parameters
  UBX_CFG_RST_NAVBBRMASK_pos =    0b0000000000010000, // Position
  UBX_CFG_RST_NAVBBRMASK_clkd =   0b0000000000100000, // Clock drift
  UBX_CFG_RST_NAVBBRMASK_osc =    0b0000000001000000, // Oscillator parameter
  UBX_CFG_RST_NAVBBRMASK_utc =    0b0000000010000000, // UTC correction + GPS leap seconds parameters
  UBX_CFG_RST_NAVBBRMASK_rtc =    0b0000000100000000, // RTC
  UBX_CFG_RST_NAVBBRMASK_sfdr =   0b0001000000000000, // SFDR Parameters (only available on the ADR/UDR/HPS product variant) and weak signal compensation estimates
  UBX_CFG_RST_NAVBBRMASK_vmon =   0b0010000000000000, // SFDR Vehicle Monitoring Parameter (only available on the ADR/UDR/HPS product variant)
  UBX_CFG_RST_NAVBBRMASK_tct =    0b0100000000000000, // TCT Parameters (only available on the ADR/UDR/HPS product variant)
  UBX_CFG_RST_NAVBBRMASK_aop =    0b1000000000000000, // Autonomous orbit parameters
} ubx_cfg_rst_navbbrmasK_t;

typedef enum {
  UBX_CFG_RST_NAVBBRMASK_HOT_START =  0x0000,
  UBX_CFG_RST_NAVBBRMASK_WARM_START = 0x0001,
  UBX_CFG_RST_NAVBBRMASK_COLD_START = 0xffff, // XXX: В u-center передается FF B9
} ubx_cfg_rst_navbbrmask_sets_t;

typedef enum {
  UBX_CFG_RST_RESETMODE_HW =          0x00, // Hardware reset (watchdog) immediately
  UBX_CFG_RST_RESETMODE_SW =          0x01, // Controlled software reset
  UBX_CFG_RST_RESETMODE_SW_GNSS =     0x02, // Controlled software reset (GNSS only)
  UBX_CFG_RST_RESETMODE_HW_SHUTDOWN = 0x04, // Hardware reset (watchdog) after shutdown
  UBX_CFG_RST_RESETMODE_GNSS_STOP =   0x08, // Controlled GNSS stop
  UBX_CFG_RST_RESETMODE_GNSS_START =  0x09  // Controlled GNSS start
} ubx_cfg_rst_resetMode_t;

typedef struct {
  uint16_t navBbrMask;
  uint8_t resetMode;
  // uint8_t reserved0
} ubx_cfg_rst_t;

int ubx_cfg_rst2array(ubx_cfg_rst_t* msg_in, uint8_t* msg_out);
