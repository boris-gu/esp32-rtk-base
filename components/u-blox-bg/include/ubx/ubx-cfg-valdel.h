#pragma once

#include <stdint.h>

typedef enum {
  UBX_CFG_VADEL_LAYERS_BBR = 0b10,
  UBX_CFG_VALDEL_LAYERS_FLASH = 0b100
} ubx_cfg_valdel_layers_t;

typedef struct {
  uint8_t version; // 0x00 without transaction
  uint8_t layers;
  // uint8_t reserved0[2]
  // TODO: Сделать для нескольких возможных пар (не больше 64)
  uint32_t key;
} ubx_cfg_valdel_t;

int ubx_cfg_valdel2array(ubx_cfg_valdel_t* msg_in, uint8_t* msg_out);
