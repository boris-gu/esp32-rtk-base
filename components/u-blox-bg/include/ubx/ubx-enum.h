#pragma once

#define UBX_SYNC1 0xB5
#define UBX_SYNC2 0x62

typedef enum {
  UBX_NAV_PVT = 0x0701, // сначала msg_id потому что little-endian
  UBX_NAV_SVIN = 0x3b01,

  UBX_ACK_ACK = 0x0105,
  UBX_ACK_NAK = 0x0005,

  UBX_CFG_RST    = 0x0406,
  UBX_CFG_VALSET = 0x8a06,
  UBX_CFG_VALGET = 0x8b06,
  UBX_CFG_VALDEL = 0x8c06
} ubx_header_t;

/**
 * U1/2/4 - uint8/16/32_t
 * I1/2/4 - int8/16/32_t
 * X1/2/4 - bitfield
 * R4/8   - float/double
 * CH     - char
 * U.*    - unsigned bitfield value of n bits width
 * I.*    - signed (two's complement) bitfield value of n bits width
 * S.*    - signed bitfield value of n bits width, in sign (most significant bit) and magnitude (remaining bits) notation
 * E1     - enumeration
 * L      - logical
 */
typedef enum {
  UBX_CFG_KEY_ALL = 0x0fff0000,
  // 6.9.11 CFG-MSGOUT: Message output configuration
  UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1005_UART1 = 0x209102be, // [ U1 | - ] Output rate of the RTCM-3X-TYPE1005 message on port UART1
  UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1005_USB =   0x209102c0, // [ U1 | - ]
  UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1077_UART1 = 0x209102cd, // [ U1 | - ]
  UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1077_USB =   0x209102cf, // [ U1 | - ]
  UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1087_UART1 = 0x209102d2, // [ U1 | - ]
  UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1087_USB =   0x209102d4, // [ U1 | - ]
  UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1097_UART1 = 0x20910319, // [ U1 | - ]
  UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1097_USB =   0x2091031b, // [ U1 | - ]
  UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1127_UART1 = 0x209102d7, // [ U1 | - ]
  UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1127_USB =   0x209102d9, // [ U1 | - ]
  UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1230_UART1 = 0x20910304, // [ U1 | - ]
  UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1230_USB =   0x20910306, // [ U1 | - ]
  
  UBX_KEY_CFG_MSGOUT_UBX_NAV_PVT_UART1 =  0x20910007, // [ U1 | - ]
  UBX_KEY_CFG_MSGOUT_UBX_NAV_PVT_USB =    0x20910009, // [ U1 | - ]
  UBX_KEY_CFG_MSGOUT_UBX_NAV_SVIN_UART1 = 0x20910089, // [ U1 | - ]
  UBX_KEY_CFG_MSGOUT_UBX_NAV_SVIN_USB =   0x2091008b, // [ U1 | - ]
  // 6.9.28 CFG-TMODE: Time mode configuration
  UBX_KEY_CFG_TMODE_MODE =           0x20030001, // [ E1 | - ]      Receiver mode
  UBX_KEY_CFG_TMODE_SVIN_MIN_DUR =   0x40030010, // [ U4 | s ]      Survey-in minimum duration
  UBX_KEY_CFG_TMODE_SVIN_ACC_LIMIT = 0x40030011, // [ U4 | 0.1mm ]  Survey-in position accuracy limit
  // 6.9.31 CFG-UART1: Configuration of the UART1 interface
  UBX_KEY_CFG_UART1_BAUDRATE =   0x40520001, // [ U4 | - ] The baud rate that should be configured on the UART1
  UBX_KEY_CFG_UART1_STOPBITS =   0x20520002, // [ E1 | - ] Number of stopbits that should be used on UART1
  UBX_KEY_CFG_UART1_DATABITS =   0x20520003, // [ E1 | - ] Number of databits that should be used on UART1
  UBX_KEY_CFG_UART1_PARITY =     0x20520004, // [ E1 | - ] Parity mode that should be used on UART1
  UBX_KEY_CFG_UART1_ENABLED =    0x10520005, // [ L  | - ] Flag to indicate if the UART1 should be enabled
  // 6.9.33 CFG-UART1OUTPROT: Output protocol configuration of the UART1 interface
  UBX_KEY_CFG_UART1OUTPROT_UBX =    0x10740001, // [ L  | - ] Flag to indicate if UBX should be an output protocol on UART1
  UBX_KEY_CFG_UART1OUTPROT_NMEA =   0x10740002, // [ L  | - ] Flag to indicate if NMEA should be an output protocol on UART1
  UBX_KEY_CFG_UART1OUTPROT_RTCM3X = 0x10740004, // [ L  | - ] Flag to indicate if RTCM3X should be an output protocol on UART1
  // 6.9.39 CFG-USBOUTPROT: Output protocol configuration of the USB interface
  UBX_KEY_CFG_USBOUTPROT_UBX =    0x10780001, // [ L  | - ] Flag to indicate if UBX should be an output protocol on USB
  UBX_KEY_CFG_USBOUTPROT_NMEA =   0x10780002, // [ L  | - ] Flag to indicate if NMEA should be an output protocol on USB
  UBX_KEY_CFG_USBOUTPROT_RTCM3X = 0x10780004, // [ L  | - ] Flag to indicate if RTCM3X should be an output protocol on USB
} ubx_cfg_key_t;