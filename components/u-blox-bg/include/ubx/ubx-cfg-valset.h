#pragma once

#include <stdint.h>

/**
 * Пример: sync  header len   ver layers reserved cfg data (key) value        checksum
 *         B5 62 06 8A  0C 00 00  01     00 00    10 00 03 40    3C 00 00 00  2C EB
 */
typedef enum {
  UBX_CFG_VALSET_LAYER_RAM = 0b1,
  UBX_CFG_VALSET_LAYER_BBR = 0b10,
  UBX_CFG_VALSET_LAYER_FLASH = 0b100
} ubx_cfg_valset_layer_t;

/**
 * U1/2/4 - uint8/16/32_t
 * I1/2/4 - int8/16/32_t
 * X1/2/4 - bitfield
 * R4/8   - float/double
 * CH     - char
 * U.*    - unsigned bitfield value of n bits width
 * I.*    - signed (two's complement) bitfield value of n bits width
 * S.*    - signed bitfield value of n bits width, in sign (most significant bit) and magnitude (remaining bits) notation
 * E1     - Вероятно, Enumeration
 */
typedef enum {
  UBX_CFG_VALSET_KEY_TMODE_MODE = 0x20030001,           // [ E1 | - ]      Receiver mode
  UBX_CFG_VALSET_KEY_TMODE_SVIN_MIN_DUR = 0x40030010,   // [ U4 | s ]      Survey-in minimum duration
  UBX_CFG_VALSET_KEY_TMODE_SVIN_ACC_LIMIT = 0x40030011  // [ U4 | 0.1mm ]  Survey-in position accuracy limit
} ubx_cfg_valset_key_t;

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
  uint8_t cfgData_value[8]; // заполнять по указателю или через memcpy
} ubx_cfg_valset_t;

int ubx_cfg_valset2array(ubx_cfg_valset_t* msg_in, uint8_t* msg_out);