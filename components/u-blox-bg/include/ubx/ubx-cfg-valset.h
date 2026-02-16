/**
 * Пример: sync  header len   ver layers reserved cfg data (key) value        checksum
 *         B5 62 06 8A  0C 00 00  01     00 00    10 00 03 40    3C 00 00 00  2C EB
 */
#pragma once

#include <stdint.h>

typedef enum {
  UBX_CFG_VALSET_LAYERS_RAM = 0b1,
  UBX_CFG_VALSET_LAYERS_BBR = 0b10,
  UBX_CFG_VALSET_LAYERS_FLASH = 0b100
} ubx_cfg_valset_layers_t;

typedef enum {
  UBX_CFG_VALSET_TMODE_MODE_DISABLED,
  UBX_CFG_VALSET_TMODE_MODE_SURVEY_IN,
  UBX_CFG_VALSET_TMODE_MODE_FIXED, // True ARP position information required
} ubx_cfg_valset_tmode_mode_t;

typedef struct {
  uint8_t version; // 0x00 without transaction
  uint8_t layers;
  // uint8_t reserved0[2]
  // TODO: Сделать для нескольких возможных пар (не больше 64)
  uint32_t cfgData_key;
  uint8_t cfgData_value_size;
  uint32_t cfgData_value; // заполнять по указателю или через memcpy
} ubx_cfg_valset_t;

int ubx_cfg_valset2array(ubx_cfg_valset_t* msg_in, uint8_t* msg_out);
