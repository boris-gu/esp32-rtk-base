#include <stdio.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <driver/uart.h>
#include "ubx.h"

#define GPIO17_U2TX 17
#define GPIO17_U2RX 16
#define UART_F9P UART_NUM_2

#define CORE_0 0
#define TASK_PRIO_LOW 1
#define TASK_PRIO_MID 2
#define TASK_PRIO_HIGH 3

void uart_setup (uart_port_t uart_num, int baudrate, int tx_pin, int rx_pin);

void uart_rx_task();
void uart_tx_task();

void prinf_msg(uint8_t* msg, uint16_t msg_size);
void send_valset (uint8_t* buff_tx, ubx_cfg_key_t key, uint8_t value_size, uint32_t value);

void app_main(void) {
  const TickType_t task_period = pdMS_TO_TICKS(2000);
  uart_setup(UART_NUM_0, 115200, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  uart_setup(UART_F9P, 38400, 17, 16);
  
  xTaskCreatePinnedToCore(uart_rx_task, "uart_rx", 10240, NULL, TASK_PRIO_HIGH, NULL, CORE_0);
  xTaskCreatePinnedToCore(uart_tx_task, "uart_tx", 10240, NULL, TASK_PRIO_HIGH, NULL, CORE_0);

  TickType_t last_time = 0;
  for (;;) {
    xTaskDelayUntil(&last_time, task_period);
  }
}

void uart_setup (uart_port_t uart_num, int baudrate, int tx_pin, int rx_pin) {
  uart_config_t uart_config = {
    .baud_rate = baudrate,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
  };
  ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
  ESP_ERROR_CHECK(uart_set_pin(uart_num, tx_pin, rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
  ESP_ERROR_CHECK(uart_driver_install(uart_num, 512, 512, 0, NULL, 0));
}

void uart_rx_task() {
  const TickType_t task_period = pdMS_TO_TICKS(10);

  const size_t BUFF_TX_SIZE = 256;
  uint8_t buff_rx[BUFF_TX_SIZE];
  int buff_rx_used = 0;
  size_t rx_available = 0;

  ubx_default_msg_t rx_msg;
  ubx_read_track_t rx_track;
  ubx_nav_svin_t rx_svin;
  ubx_nav_pvt_t rx_pvt;

  TickType_t last_time = 0;
  for(;;) {
    if (uart_get_buffered_data_len(UART_F9P, &rx_available) == ESP_FAIL) {
      rx_available = 0;
      continue;
    }
    rx_available = rx_available < BUFF_TX_SIZE ? rx_available : BUFF_TX_SIZE;
    buff_rx_used = uart_read_bytes(UART_F9P, buff_rx, rx_available, 1);

    for (int i = 0; i < buff_rx_used; i++) {
      if (ubx_parse_char(buff_rx[i], &rx_msg, &rx_track)) {
        switch (rx_msg.header) {
          // case UBX_NAV_PVT:
          //   printf("GET UBX_NAV_PVT\n");
          //   ubx_default_msg_t2ubx_nav_pvt(&rx_msg, &rx_pvt);
          //   printf("\tFix Mode: ");
          //   switch (rx_pvt.fixType) {
          //     case UBX_NAV_PVT_FIXTYPE_NOFIX:
          //       printf("No Fix");
          //       break;
          //     case UBX_NAV_PVT_FIXTYPE_DR:
          //       printf("Dead Reckoning");
          //       break;
          //     case UBX_NAV_PVT_FIXTYPE_2D:
          //       printf("2D Fix");
          //       break;
          //     case UBX_NAV_PVT_FIXTYPE_3D:
          //       printf("3D Fix");
          //       break;
          //     case UBX_NAV_PVT_FIXTYPE_GNSS_DR:
          //       printf("GNSS+DR");
          //       break;
          //     case UBX_NAV_PVT_FIXTYPE_TIME:
          //       printf("TIME");
          //       break;
          //   }
          //   if (get_ubx_nav_pvt_flags_diffSoln(&rx_pvt)){
          //     switch (get_ubx_nav_pvt_flags_carrSoln(&rx_pvt)) {
          //       case 0:
          //         printf("/DGNSS"); // XXX: Возможно RTK, но без решения?
          //         break;
          //       case 1:
          //         printf("/RTK FLOAT");
          //         break;
          //       case 2:
          //         printf("/RTK FIX");
          //         break;
          //     }
          //   }
          //   printf ("\n");
          //   printf("\tUTC+0: %02d:%02d:%02d\n", rx_pvt.hour, rx_pvt.min, rx_pvt.sec);
          //   printf("\tlat:  %ld.%07d\n", rx_pvt.lat / 10000000, abs(rx_pvt.lat) % 10000000);
          //   printf("\tlon:  %ld.%07d\n", rx_pvt.lon / 10000000, abs(rx_pvt.lon) % 10000000);
          //   printf("\thAcc: %ld\n", rx_pvt.hAcc);
          //   printf("\tvAcc:  %ld\n", rx_pvt.vAcc);
          //   break;
          // case UBX_NAV_SVIN:
          //   printf("GET UBX_NAV_SVIN\n");
          //   ubx_default_msg_t2ubx_nav_svin(&rx_msg, &rx_svin);
          //   printf("\tactive:  %u\n", rx_svin.active);
          //   printf("\tvalid:   %u\n", rx_svin.valid);
          //   printf("\tdur:     %lu s\n", rx_svin.dur);
          //   printf("\tmeanAcc: %.2f m\n", rx_svin.meanAcc / 10000.);
          //   break;
          case UBX_ACK_ACK:
            printf("GET UBX_ACK_ACK\n");
            break;
          case UBX_ACK_NAK:
            printf("GET UBX_ACK_NAK\n");
            break;
          default :
            // printf("GET MSG %#04x\n", rx_msg.header);
            break;
        }
        if (rx_msg.header == UBX_ACK_ACK || rx_msg.header == UBX_ACK_NAK) {
          uart_write_bytes(UART_NUM_0, &rx_msg.header, 2);
        }
      }
    }
    xTaskDelayUntil(&last_time, task_period);
  }
}

void uart_tx_task() {

  const TickType_t task_period = pdMS_TO_TICKS(1000);
  
  const size_t BUFF_TX_SIZE = 256;
  uint8_t buff_tx[BUFF_TX_SIZE];
  int buff_tx_used = 0;

  vTaskDelay(pdMS_TO_TICKS(2000));
  
  printf("---\n VALDEL\n---\n\n");
  ubx_cfg_valdel_t valdel;
  valdel.version = 0x00;
  valdel.layers = UBX_CFG_VADEL_LAYERS_BBR | UBX_CFG_VALDEL_LAYERS_FLASH;
  valdel.key = UBX_CFG_KEY_ALL;
  buff_tx_used = ubx_cfg_valdel2array(&valdel, buff_tx);
  uart_write_bytes(UART_F9P, buff_tx, buff_tx_used);
  prinf_msg(buff_tx, buff_tx_used);
  vTaskDelay(pdMS_TO_TICKS(2000));

  printf("---\n RESET\n---\n\n");
  ubx_cfg_rst_t rst;
  rst.navBbrMask = UBX_CFG_RST_NAVBBRMASK_HOT_START;
  rst.resetMode = UBX_CFG_RST_RESETMODE_SW;
  buff_tx_used = ubx_cfg_rst2array(&rst, buff_tx);
  uart_write_bytes(UART_F9P, buff_tx, buff_tx_used);
  prinf_msg(buff_tx, buff_tx_used);
  vTaskDelay(pdMS_TO_TICKS(2000));

  printf("---\n MSGOUT\n---\n\n");
  send_valset (buff_tx, UBX_KEY_CFG_MSGOUT_UBX_NAV_PVT_UART1, 1, 1);
  send_valset (buff_tx, UBX_KEY_CFG_MSGOUT_UBX_NAV_SVIN_UART1, 1, 1);
  send_valset (buff_tx, UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1005_UART1, 1, 1);
  send_valset (buff_tx, UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1077_UART1, 1, 1);
  send_valset (buff_tx, UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1087_UART1, 1, 1);
  send_valset (buff_tx, UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1097_UART1, 1, 1);
  send_valset (buff_tx, UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1127_UART1, 1, 1);
  send_valset (buff_tx, UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1230_UART1, 1, 1);

  send_valset (buff_tx, UBX_KEY_CFG_MSGOUT_UBX_NAV_PVT_USB, 1, 1);
  send_valset (buff_tx, UBX_KEY_CFG_MSGOUT_UBX_NAV_SVIN_USB, 1, 1);
  send_valset (buff_tx, UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1005_USB, 1, 1);
  send_valset (buff_tx, UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1077_USB, 1, 1);
  send_valset (buff_tx, UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1087_USB, 1, 1);
  send_valset (buff_tx, UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1097_USB, 1, 1);
  send_valset (buff_tx, UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1127_USB, 1, 1);
  send_valset (buff_tx, UBX_KEY_CFG_MSGOUT_RTCM_3X_TYPE1230_USB, 1, 1);
  
  vTaskDelay(pdMS_TO_TICKS(2000));

  printf("---\n SURVEY IN\n---\n\n");
  send_valset (buff_tx, UBX_KEY_CFG_TMODE_SVIN_MIN_DUR, 4, 60);
  send_valset (buff_tx, UBX_KEY_CFG_TMODE_SVIN_ACC_LIMIT, 4, 300000);
  send_valset (buff_tx, UBX_KEY_CFG_TMODE_MODE, 1, UBX_CFG_VALSET_TMODE_MODE_SURVEY_IN);

  TickType_t last_time = 0;
  for(;;) {
    xTaskDelayUntil(&last_time, task_period);
  }
}

void prinf_msg(uint8_t* msg, uint16_t msg_size) {
  for (int i = 0; i < msg_size; i++) {
    printf("%02X ", msg[i]);
  }
  printf("\n");
}

void send_valset (uint8_t* buff_tx, ubx_cfg_key_t key, uint8_t value_size, uint32_t value) {
  ubx_cfg_valset_t valset;
  valset.version = 0x00;
  valset.layers = UBX_CFG_VALSET_LAYERS_RAM;
  valset.cfgData_key = key;
  valset.cfgData_value_size = value_size;
  valset.cfgData_value = value;
  int buff_tx_used = ubx_cfg_valset2array(&valset, buff_tx);
  uart_write_bytes(UART_F9P, buff_tx, buff_tx_used);
  prinf_msg(buff_tx, buff_tx_used);
}